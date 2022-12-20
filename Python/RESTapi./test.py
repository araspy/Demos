import requests
import json

# GET ----------------------------------------------------------------------------------------------
"""
basic request of all the data under the API's users URL

URL = "https://jsonplaceholder.typicode.com/users"

response = requests.get(URL)

print(response.text)

"""

"""
getting data filtered by user input on username

URL = "https://jsonplaceholder.typicode.com/users"

print("Search by Username:")
user = input("> ")
queryURL = URL + f"?username={user}"

response = requests.get(queryURL)

print(response.text)


"""

URL = "https://jsonplaceholder.typicode.com/users"

print("Search by Username:")
user = input("> ")
queryURL = URL + f"?username={user}"
response = requests.get(queryURL)

userdata = json.loads(response.text)[0]

name = userdata["name"]
email = userdata["email"]
phone = userdata["phone"]

print(f"{name} can be reached via the following methods:")
print(f"Email: {email}")
print(f"Phone: {phone}")


# POST --------------------------------------------------------------------------------
payload = {'key1': 'value1', 'key2': 'value2'}
# instead of passing data, we can pass json={"key":"value"}
r = requests.post("https://httpbin.org/post", data=payload)
print(r.text)
"""
{
...
    "from": {
        "key2": "value2",
        "key1": "value1"
    }
    ...
}
"""
# doing a file post
url = 'https://httpbin.org/post'
files = {'file': open('report.xls', 'rb')}

r = requests.post(url, files=files)
r.text
{
    "files":{
        "file": "<censored...binary...data>"
    }
}

# DELETE ------------------------------------------------------------------------------------------
id = input("Which emp id u wanna delete?")
response = requests.delete(f"URL/employees/{id}")
print(response.json())
print(response.status_code)


# POST --------------------------------------------------------------------------------------------
name = input("name of who u wanna delete: ")
employee = { "name": name }
headers = {"Content-type": "application/json"}
response = requests.post("http://localhost:5000/employees", json=employee, headers=headers)
print(response.content)
print(response.headers)
print(response.status_code)


# PUT ---------------------------------------------------------------------------------------------

id = input("which employee u wanna update")
name = input("what u wanna change the name to: ")
employee = { "name": name }
headers = {"Content-type": "application/json"}
response = requests.put(f"http://localhost:5000/employees{id}", json=employee, headers=headers)
print(response.json())
print(response.status_code)