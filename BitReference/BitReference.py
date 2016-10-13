# coding=utf-8
import socket, urllib,  sys
import re, urllib, urllib2, urlparse, os

FailedPages = []
#/////////////////////////////////////////////
# @param url(type string)
# Check bit urls in getted "url"
#/////////////////////////////////////////////
usedUrls = []
failedUrl = []
queuedURL = ""

def CheckReference(page):
    try:
        code = urllib.urlopen(page).getcode()
        # 2xx - Success
        # 301 Moved Permanently — запрошенный документ был окончательно перенесен на новый URI,
        #  указанный в поле Location заголовка. Некоторые клиенты некорректно ведут себя при
        # обработке данного кода. Появился в HTTP/1.0.

        # 302 Found, 302 Moved Temporarily — запрошенный документ временно доступен
        # по другому URI, указанному в заголовке в поле Location. Этот код может
        # быть использован, например, при управляемом сервером согласовании
        # содержимого. Некоторые клиенты некорректно ведут себя при обработке
        # данного кода. Введено в HTTP/1.0.
        if (code not in [200, 301]):
            status = str(code)
            failedUrl.append(page + " " + status)
            # print message if not internet


    except IOError as err:
        #print("IOError error: {0}".format(err))
        print "Невозможно открыть указанную страницу {0}. Пожалуйста, проверьте соединение с интернетом.".format(page)
    else:
        status = str(code)
        usedUrls.append(page + " " + status)


def CheckLinksFromPage(url):
    if not (url in usedUrls):
        usedUrls.append(url)
        content = urllib2.urlopen(url).read()

        # Find address data
        DataUrls = re.findall('href="(.*?)"', content)

        # Conversion in absolute address
        convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in DataUrls]

        for urlList in convertDataUrls:
            nameFile = urlList.rsplit('/', 1)[-1]
            if '.htm' in nameFile or '.html' in nameFile:
                # Check if the reference breaked
                CheckReference(urlList)

# /////////////////////////////////////////////#
# \/              Main                     \/ #
def MainFunction(argv):
    
    if (len(sys.argv) == 1):
        queuedURL = raw_input("Укажите адрес страницы в качестве параметра. "
                              "Формат ввода link_checker.exe http://path-to-site.com. "
                              "Введите URL: ")
    else:
        queuedURL = argv[1]


    isErrorInURL = True
    while (isErrorInURL):
        try:
            CheckLinksFromPage(queuedURL)
            break
        except urllib2.URLError as err:
            queuedURL = raw_input("Введенный адрес не является корректным URL."
                                  "Пожалуйста, введите адрес в формате http://path-to-site.com"
                                  "Введите URL: ")

    correctRef = open("AllReference.txt", 'w')
    for url in usedUrls:
        correctRef.write(url + '\n')
    correctRef.close()

    incorrectRef = open("InvalidRefernce.txt", 'w')
    for url in failedUrl:
        incorrectRef.write(url + '\n')
    incorrectRef.close()

    print ("Program executed")

    #"https://www.python.org/"
#/////////////////////////////////////////////#

MainFunction(sys.argv)