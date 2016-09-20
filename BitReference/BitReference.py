import re, urllib, urllib2, urlparse, os

#/////////////////////////////////////////////
# @param url(type string)
# Check bit urls in getted "url"
#/////////////////////////////////////////////
def checkBitReference(url):
    if not (url in usedUrls):
        usedUrls.append(url)
        content = urllib2.urlopen(url).read()

        #print url# I want know current url

        # Find address data
        DataUrls = re.findall('href="(.*?)"', content)

        # Conversion in absolute address
        convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in DataUrls]


        for urlList in convertDataUrls:
            nameFile = urlList.rsplit('/', 1)[-1]
            if '.htm' in nameFile or '.html' in nameFile:
                checkBitReference(urlList)
#/////////////////////////////////////////////
# @param url(type string)
# Check bit url or not
#/////////////////////////////////////////////
def CheckSait(url):
    f = 0;# TODO : write


#/////////////////////////////////////////////#
# \/              Main                     \/ #

url = "https://www.python.org/"

usedUrls = []
checkBitReference(url)
#/////////////////////////////////////////////#