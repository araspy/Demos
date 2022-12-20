import requests
import json

URL = "https://api.meraki.com/api/v1"

APIKEY = {"X-Cisco-Meraki-API-Key": "<INSERT MERAKI API KEY>"}


def getOrgID():
    """
    Query Meraki API for which Organizations we have access to and return Org ID
    Theres only one org in this json file example. so [0] to just pull the
    first ID
    :return:
    """
    queryURL = URL + "/organizations"
    response = requests.get(queryURL, headers=APIKEY)
    orgID = json.loads(response.text)[0]["id"]
    return orgID


def getNetworks(orgID):
    """
    Use Organization ID to pull list of networks we have access to
    notice how not only you can append to the url strings to
    get different data but also use string literals to plug
    dynamic changing stuff if you need different parts of the url data
    :param orgID:
    :return: a list of networks under the org
    """
    queryURL = URL + f"/organizations/{orgID}/networks"
    response = requests.get(queryURL, headers=APIKEY)
    data = json.loads(response.text)
    networkList = []
    for network in data:
        networkList.append(network["id"])
    return networkList


def getClients(orgID, networkList):
    """
    Query clients for each network and return the client list
    :param orgID: orgs we have access to
    :param networkList: list of networks based on the org id
    :return: client list
    """
    clientCount = {}
    total = 0
    # Query parameters: return up to 100 devices seen in the last 43200 seconds(30 days)
    q = {"perPage" : "100",
         "timespan" : "43200"}
    for network in networkList:
        # Query clients for each network
        queryURL = URL + f"/networks/{network}/clients"
        response = requests.get(queryURL, params=q, headers=APIKEY)
        data = json.loads(response.text)
        # Grab client OS from each device and append to clientCount dictionary
        for client in data:
            try:
                clientCount[client["os"]] += 1
            except KeyError:
                clientCount[client["os"]] = 1
            except TypeError:
                continue
            total += 1
    # Append final count of all devices & return dict
    clientCount["Total Devices"] = total
    return clientCount

def printReport(clientOS):
    """
    Print final output to terminal
    :param clientOS:
    :return:
    """
    print("Count of clients by operating system:")
    for OS in clientOS:
        print(f"{OS}: {clientOS[OS]}")


if __name__ == '__main__':
    orgID = getOrgID()
    networkList = getNetworks(orgID)
    clientOS = getClients(orgID, networkList)
    printReport(clientOS)



