#PANDAS
#two fundamental data structures in pandas:
#Series: a 1-D array
#Data Frame: a 2d array of two or more Series joined together

import pandas as pd

pd.options.display.max_columns = 15


#handling other formats
#df_xlsx = pd.read_excel('pokemon_data')
#df = pd.read_csv('pokemon_data.txt', delimiter='\t') #tab separated text file
df = pd.read_csv('pokemon_data.csv')

#print(df)
#print(df.head(3)) #just grabbing top x rows
#print(df.tail(3)) # bottom x rows

#Read Headers
#print(df.columns)


#Read each Column
#print(df['Name'][0:5])
#print(df[['Name', 'Type 1', 'HP']])


#Read Each Row
#print(df.iloc[1])  #iloc = integer location. this gives you everything in x row
#print(df.iloc[1:4])
#for index, row in df.iterrows():
#   print(index, row['Name'])
#print(df.loc[df['Type 1'] == "Fire"]) #grab fire type pokemon

#Read a specific location (R, C)
#print(df.iloc[2,1])


#Get High Level Stats
#print(df.describe())


#Sorting values
#print(df.sort_values('Name'))
#df.sort_values('Name', ascending=False) # sort by alphabet but descending
#df.sort_values(['Type 1', 'HP'], ascending= [1,0]) #gives us Bug pokemon sorted by hp descending


#Manipulating data
#creating a total stat points column:
#df['Total'] = df['HP'] + df['Attack'] + df['Defense'] + df['Sp. Atk'] + df['Sp. Def'] + df['Speed']
#print(df.head(10))

#drop the total stat points column:
#df.drop(columns=['Total'])
#or
#df = df.drop(columns=['Total'])
#print(df.columns)

#another way to create total stat points column
#axis = 1 means add horizontally, 0 implies vertically. the first : just means all the rows
#indexing is "exclusive", meaning the 10th column is the first one we exclude
#df['Total'] = df.iloc[:, 4:10].sum(axis=1)

#moving the total columns in front of the stats:
#cols = list(df.columns)
#df = df[cols[0:4] + [cols[-1]] + cols[4:12]]
#print(df.head(10))



#Saving our new CSV
#df.to_csv('modified.csv', index = False)
#other formats:
#df.to_excel('modified.xlsx', index = False)
#df.to_csv('modified.txt', index = False, sep='\t')


#Advanced Filtering
#dont forget you can save these queries as a new_df =
#then you can save them to a new / separate csv
#new_df.reset_index(drop=True, inplace=True) # get new indices in new file
#print(df.loc[(df['Type 1'] == 'Grass') & (df['Type 2'] == 'Poison')]) #can use OR | instead of course
#print(df.loc[(df['Type 1'] == 'Grass') & (df['Type 2'] == 'Poison') & (df['HP'] > 70)])

#df.loc[~df['Name'].str.contains('Mega')] #drop any with mega in name
#using regex to find stuff.
# re.I is ignore case. finding if pokemon type 1 is fire or grass.
#import re
#df.loc[df['Type 1'].str.contains('fire|grass', flags=re.I, regex=True)]
#find pokemon like pikachu and pigeotto. asterisk means 0 or more. carrot is 'begins with'
#df.loc[df['Name'].str.contains('^pi[a-z]*', flags=re.I, regex=True)]


#Conditional Changes
#change name of fire type:
#df.loc[df['Type 1'] == 'Fire', 'Type 1'] = 'Flamer'
#set fire type pokemon to legendary:
#df.loc[df['Type 1'] == 'Fire', 'Legendary'] = True
#change multiple parameters at a time:
#df.loc[df['Total'] > 500, ['Generation', 'Legendary']] = ['TEST VALUE1'. 'TEST VALUE2']



#Aggregate Statistics (Groupby)
#see average stats of types
#print(df.groupby(['Type 1']).mean())
#print(df.groupby(['Type 1']).mean().sort_values('Defense', ascending=False))
#df.groupby(['Type 1']).sum()
#see how many of each with type1:
#df['count'] = 1
#print(df.groupby(['Type 1']).count()['count'])
#print(df.groupby(['Type 1', 'Type 2']).count()['count'])



#Working with large amounts of data
#make a new dataframe that is a shrunken down version of the massive one:
#new_df = pd.DataFrame(columns = df.columns)
#for df in pd.read_csv('modified.csv', chunksize = 5) :
    #results = df.groupby(['Type 1']).count()

    #new_df = pd.concat([new_df, results])



#can also read from html site (if it has a table) and SQL DB and JSON
#df = pd.read_html(url)
#df = pd.read_sql("query")
#df = pd.read_json()


#user input
#country = input('Enter country name: ')

#connections
#conn = MySQLdb.connect(host="112.0.0.1", port=3306, user="root",passwd="root",db="world")

#dataframe produced by parameterized query
#df = pd.read_sql("SELECT * FROM COUNTRY WHERE Name = '%s'" %(country,), conn)
#print(df)




#json read
#import json
#emp_records_json_str = json.dumps(EmployeeRecords)
#df = pd.read_json(emp_records_json_str, orient='records', convert_dates=['DOJ'])
#print(df)


#converting a time column to Pandas' special datetime format to do some fun organization stuff:
#ufo = pd.read_csv('link')
#ufo['Time'] = pd.to_datetime(ufo.Time)
#Time column is no longer string
#ufo.Time.dt.hour #pulls out the hour for us
#ufo.Time.dt.weekday_name
#ufo.Time.dt.weekday # just pulls the number
#ufo.Time.dt.dayofyear # pulls like, 152
#can use timestamps as part of comparisons
#ts = pd.to_datetime('1/1/1999')
#ufo.loc[ufo.Time >= ts, :] #colon just means show me all columns
#ufo.Time.max() #shows latest time in timeseries
#ufo.Time.max() - ufo.Time.min() #find gap covered by data
#(ufo.Time.max() - ufo.Time.min()).days #just get it in days

#analyze how many reported sightings by year
#%matplotlib inline

#ufo['Year'] = ufo.Time.year
#ufo.Year.value_counts().sort_index().plot()


#Hierarchical Indexing (MultiIndex)- having more than one index in dataframe
df.set_index(['city', 'rank'] drop = False) #drop false = don't get rid of these columns just use them as a n index







