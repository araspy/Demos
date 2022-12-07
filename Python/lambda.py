import json

#example hello world
def lambda_handler(even, context):
    return {
        'statusCode': 200,
        'body' : json.dumps('Hello from Lambda!')
    }


# example list buckets
import json
import boto3

s3 = boto3.resource('s3')

def lambda_handler(event, context):
    bucket_list = []
    for bucket in s3.buckets.all():
        print(bucket.name)
        bucket_list.append(bucket.name)
    return {
        'status': 200,
        'body': bucket_list
    }


# example get items
import json
import boto3

dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('planets')

def lambda_handler(event, context):
    response = table.get_item(
        Key={
            'id': 'mercury'
        }
    )
    print(response)
    return {
        'statusCode': 200,
        'body': response
    }


# example put items
import json
import boto3

dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('planets')

def lambda_handler(event, context):
    table.put_item(
        Item={
            'id': 'neptune',
            'temp': 'super cold'
        }
    )
    response = {
        'message': 'Item added'
    }
    return {
        'statusCode': 200,
        'body': response
    }



# Boto3
# can interact with lots of AWS services so you need to specify the client.
import boto3

s3_client = boto3.client('s3')

s3_client.create_bucket(Bucket = "Bucket-Name", CreateBucketConfiguration={'LocationConstraint':'na-east-1'})

response = s3_client.list_buckets()
print(response)


def upload_files(file_name, bucket, object_name = None, args=None):
    """

    :param file_name: name of file on local
    :param bucket: bucket name
    :param object_name: name of file on s3
    :param args: custom args
    :return:
    """
    if object_name is None:
        object_name = file_name

    response = s3_client.upload_file(file_name, bucket, object_name, ExtraArgs=args)

    print(response)




upload_files('data/panda-19383_394.jpg', 'serverbucket')


# uploading multiple files to s3
import glob

files = glob.glob('folder/*')

# ACL = access control list
args = {'ACL': 'public-read'}

for file in files:
    upload_files(file, 's3bucket', args = args)
    print('uploaded ', file)


# download files from s3
# key = file to which you want to write the data
list(s3.buckets.all())
s3_client.list_buckets()

bucket = s3.Bucket('bucketName')
list(bucket.objects.all())

for file in files:
    s3_client.download_file('s3bucketname', file.key, file.key)

"""
bucket policy to handle bucket file handling
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicRead",
            "Effect": "Allow",
            "Principal": "*",
            "Action": [
                "s3:GetObject",
                "s3:GetObjectVersion"
            ],
            "Resource": [
                "arn:aws:s3:::DOC-EXAMPLE-BUCKET/*"
            ]
        }
    ]
}
"""
import json
bucket_name = 'bucketname'
bucket_policy = {
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicRead",
            "Effect": "Allow",
            "Principal": "*",
            "Action": [
                "s3:GetObject",
                "s3:GetObjectVersion"
            ],
            "Resource": [
                "arn:aws:s3:::DOC-EXAMPLE-BUCKET/*"
            ]
        }
    ]
}

bucket_policy = json.dumps(bucket_policy)
s3_client.put_bucket_policy(Bucket=bucket_name, Policy=bucket_policy)

# if you wanna check what policies are on a bucket
s3_client.get_bucket_policy(Bucket=bucket_name)


# using put_object instead
data = {"name":"aws-made-easy"}
data = json.dumps(data).encode('UTF-8')

s3_client.put_object(Body=data, Bucket='my-bucket-5483298', Key='new_file')


#using get_object instead
response = s3_client.get_object(Bucket='my-bucket-390584', Key='json_data.json') # path for keynot just file name

data = response['Body'].read()
print(data)




"""
EXAMPLE-------------------------------
I want to create a lambda function that uses an Athena query

Steps:
1. create IAM role which grants Lambda the access to run Athena Queries
2. Define Lambda function. Write Py script to run Athena query and get results.
3. execute. run your lambda function and view results in the console, or you 
can store the results to an s3 bucket if you need. 

"""
"""
permissions granted (policy for IAM role):

{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "glue:GetDatabase",
                "glue:GetDatabases",
                "glue:GetTable",
                "glue:GetTables",
                "Athena:StartQueryExecution",
                "Athena:GetQueryExecution",
                "Athena:GetQueryResults",
                "s3:GetObject",
                "s3:GetBucketLocation",
                "s3:PutObject",
                "s3:ListBucket"
            ],
            "Resource": "*"
        }
    ]
}

"""

import json
import boto3
import time

def lambda_handler(event, context):
    my_query = 'SELECT * FROM org_sample_data'
    database_name = 'organisation'

    athena_client = boto3.client('athena')

    QueryResponse = athena_client.start_query_execution(
        QueryString=my_query,
        QueryExecutionContext = {
            'Database': database_name
        },
        ResultConfiguration= {
            'OutputLocation': 's3://aws-athena-query-results-948747383-us-east-2/'
        }
        )

    QueryID = QueryResponse['QueryExecutionId']

    time.sleep(15)

    query_results = athena_client.get_query_results(QueryExecutionId=QueryID)

    for row in query_results['ResultSet']['Rows']:
        print(row)
