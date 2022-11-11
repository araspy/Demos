#GLUE NOTES
#aws glue data catalog is a persistent metadata store
#managed service that lets you store, annotate, and share metadata
#which can be used to query/transform data
#folders where data is stored, which are physical entities, are mapped to partitions,
#which are logical entities i.e. columns in the Glue table.

#AWS GLUE CRAWLER:
#program that connects to data store (source/target), progresses through a prioritized
#list of classifiers to determine the schema for your data, and then creates
#metadata tables in the AWS Glue Data Catalog


#Glue Develope Endpoint is a ide that can be used

#Data Lake: centralized repository that allows you to store all you structured and
#unstructured dat at any scale.


#Creating a glue job: type = spark, glue version = spark2.4, python 3
#opens up a job area where you can write your scripting code
#running the job can take some time to finish, especially with big data










#PYSPARK NOTES
#Python API for Spark, used for big data processing
#interfaces with Resilient Distributed Datasets(RDDs) in apache spark.
#ETL
#Extract: Check schema, Query, filter data
#Transform: Manipulate data, Aggregated data, Merge/split data sets
#Load: Load / write data at the destination
#DYNAMIC FRAME VS DATA FRAME:
#DynamicFrame is safer when handling memory intensive jobs. the Spark
#DataFrame could hit "out of memory" issue on executors.
#Use dynamicframe when data does not conform to a fixed schema.
#can convert dynamic using toDF()


#Glue context connects with the Spark session and also provides access to the data lake catalog tables
import sys
from awsglue.transforms import *
from awsglue.utils import getResolvedOptions
from pyspark.context import SparkContext
from awsglue.context import GlueContext
from awsglue.job import Job

glueContext = GlueContext(SparkContext.getOrCreate())

salesDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="sales"
)
customerDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="customers"
)
#Pyspark snippet to see schema of the two dynamic frames
salesDF.printSchema()
customerDF.printSchema()

#Pyspark snippet to join salesDF and customerDF on customerid
customersalesDF = Join.apply(salesDF, customerDF, 'customerid', 'customerid')
customersalesDF.printSchema()

#You can see two columns customerid and .customerid due to the join key.
#you can use drop_fields to remove .customer_id
customersalesDF = customersalesDF.drop_fields(['`.customerid`'])
customersalesDF.printSchema()

#the dataframes are merged, let's write this merged data back to the S3 bucket.
#pyspark snippet to write it to a folder in the data lake.
glueContext.write_dynamic_frame.from_options(customersalesDF, connection_type = "s3",
connection_options = {"path": "s3://dojo-data-lake/data/customersales"}, format = "json")


#EXAMPLE 2: more pyspark/gluejob EXTRACT
#Step1 create the glue context
#import sys
#from awsglue.transforms import *
#from awsglue.utils import getResolvedOptions
#from pyspark.context import SparkContext
#from awsglue.context import GlueContext
#from awsglue.job import Job

#load the dynamicframe for the data catalog table sales in the database dojodatabase
salesDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="sales"
)
#see the column names and their data types
salesDF.printSchema()
#check number of rows in table
salesDF.count()
#show top 20 rows of the data catalog table sales
salesDF.toDF().show()
#you can pass parameters in the show function to see specified number of rows.
salesDF.toDF().show(2)
#you can use head method to query top row in a different format. you can pass number of rows as parameter
salesDF.toDF().head()
#you can make selection of columns. using selectfields.
ordersDF = SelectFields.apply(salesDF,["ordernumber", "sales"])
ordersDF.toDF().show()
#row level filering
highSalesDF = Filter.apply(salesDF, f = lambda x: x["sales"] > 12000)
highSalesDF.toDF().show()


#EXAMPLE3: TRANSFORM
#Step1 create the glue context
#import sys
#from awsglue.transforms import *
#from awsglue.utils import getResolvedOptions
#from pyspark.context import SparkContext
#from awsglue.context import GlueContext
#from awsglue.job import Job

#load data in the dynamicframe from customers table
customersDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="customers"
)

#often a simple concatenation of two fields is necessary. create a new field for full name:
def addcolumns(rec):
    rec["contactfullname"] = {}
    rec["contactfullname"] = rec["contactfirstname"] + ' ' + rec["contactlastname"]
    return rec
#apply method to use the python function for the transformation.
customersDF = Map.apply(customersDF, f = addcolumns)
customersDF.toDF().show()
#can use DropFields method since we have fullname and dont need first/last anymore
customersDF = DropFields.apply(customersDF, ["contactfirstname","contactlastname"])
customersDF.toDF().show()
#create python function to extract domain name out of an email addr
def parsedomain(rec):
    rec["domain"] = {}
    index = rec["email"].index('@')
    rec["domain"] = rec["email"][indx+1:]
    return rec
#run the function to create the new domain column
customersDF = Map.apply(customersDF, f =  parsedomain)
customersDF.toDF().show();
#renaming a field ('territory' to 'region'):
customersDF = customersDF.rename_field("territory","region")
customersDF.toDF().show();


#EXAMPLE4: AGGREGATE FUNCTIONS
#create the glue context like in previous examples

#pyspark code to load data into dynamicframe from sales table
salesDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="sales"
)
salesDF = salesDF.toDF();
salesDF.show()

#view two columns in perspective using crosstab. view the relationship between productline and dealsize columns:
salesDF.crosstab('productline', 'dealsize').show()
#describe method to see stats of a column. check stats of sales column:
salesDF.describe('sales').show()
#groupby method with a particular column along with individual aggregation function.
#see count per productline:
salesDF.groupby('productline').count().show()
#see min,max,mean,sum of quantity ordered per productline
salesDF.select("productline","quantityordered").groupby('productline').min().show()
#above, just exchange .min() with .max(),.mean(),.sum() as needed

#can use multiple aggregation in one using groupby and agg funcs.
#view average quantityordered, sum of sales and maximum priceeach per productline:
salesDF.groupby('productline').agg({'quantityordered': 'mean','sales' : 'sum','priceeach' : 'max'}).show()

#can use orderBy method to sort DataFrame for a column in asc or desc. sort sales frist ascending or desc:
salesDF.orderBy(salesDF.sales).show()
salesDF.orderBy(salesDF.sales.desc()).show()


#EXAMPLE5 : merge/split datasets
#create the glue context/connection like in previous examples


salesDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="sales"
)
customersDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="customers"
)
#check the schemas and see the tables have customerid in common
salesDF.printSchema()
customerDF.printSchema()
#remove the unneeded .customerid field
customersalesDF = customersalesDF.drop_fields(['`.customerid`'])
#can split a Dynamicframe vertically based on columns. use Splitfields metho which splits a Dynamicframe
#into a collection of Dynamic frames.
#split salesDF into two frames productsDF and rest DF. productsDF has columns productline,
#dealsize, and status. restDF has remaining columns. use keys method to check
#creation of the dynamicframe in the dynamicframe collection colwiseCollection:
colwiseCollection = SplitFields.apply(salesDF,["productline","dealsize","status"], "productsDF", "restDF")
colwiseCollection.keys()
#check the scemas of the new dfs:
colwiseCollection.select("productsDF").printSchema()
colwiseCollection.select("restDF").printSchema()
#can also split on rows. separates sales at 5000 mark:
rowwiseCollection = SplitRows.apply(salesDF,{"sales": {">": 5000.00}}, "sales5000plus", "sales5000minus")
rowwiseCollection.keys()
#check the top 20 values in the two dfs
rowwiseCollection.select("sales5000minus").toDF().select('sales').show()
rowwiseCollection.select("sales5000plus").toDF().select('sales').show()
#can use union method to merge two similar dfs row wise. merge plus and minus into allsales:
sales5000minus = rowwiseCollection.select("sales5000minus").toDF()
sales5000plus = rowwiseCollection.select("sales5000plus").toDF()
allsalesDF = sales5000plus.union(sales5000minus)
allsalesDF.show()

#EXAMPLE6: write/load data
#create the glue context/connection like in previous examples


salesDF = glueContext.create_dynamic_frame.from_catalog(
    database="dojodatabase",
    table_name="sales"
)

#create productline df that you plan to write back to another S3 location within the data lake
productlineDF = SelectFields.apply(salesDF, paths = ["productline", "dealsize", "status"])
productlineDF.printSchema()
#write the df to the productline folder within the /data S3 bucket.
glueContext.write_dynamic_frame.from_options(productlineDF, connection_type="s3", connection_options={"path": "s3://dojo-data-lake/data/productline"}, format="json")
#that was an example of ETL from S3 to S3. if you wanna do ETL with another data source like rdb or Redshift:
glueContext.write_dynamic_frame.from_jdbc_conf(productlineDF,catalog_connection = "dojoconnection",
                                               connection_options={"dbtable": "products", "database":"dojodatabase"},
                                               redshift_tmp_dir = "s3://dojo-data-lake/data/script")


