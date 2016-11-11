# coding=utf-8
import sys, re, urllib2, urlparse

usedUrls = []
listOtherRef = []
startURL = ""
correctUrls = []
urlsForCheck = []
failedUrl = []
queuedURL = ""
queuedURLS = []
pageOpen = False

def CheckReference(page):
    code = ""
    try:
        code = urllib2.urlopen(page).getcode()
        # 2xx - Success
        # 301 Moved Permanently — запрошенный документ был окончательно перенесен на новый URI,
        #  указанный в поле Location заголовка. Некоторые клиенты некорректно ведут себя при
        # обработке данного кода. Появился в HTTP/1.0.

        # 302 Found, 302 Moved Temporarily — запрошенный документ временно доступен
        # по другому URI, указанному в заголовке в поле Location. Этот код может
        # быть использован, например, при управляемом сервером согласовании
        # содержимого. Некоторые клиенты некорректно ведут себя при обработке
        # данного кода. Введено в HTTP/1.0.

        status = str(code)
        if (code not in [200, 301, 302]):
            if (page + " " + status) not in failedUrl:
                failedUrl.append(page + " " + status)
        else:
            if (page + " " + status) not in correctUrls:
                correctUrls.append(page + " " + status)
                urlsForCheck.append(page)
    except urllib2.HTTPError as err:
        if (page + " " + str(err.getcode()) ) not in failedUrl:
            failedUrl.append(page + " " + str(err.getcode()) )
    except BaseException as err:
        if (page + " " + err.__str__()) not in failedUrl:
            failedUrl.append(page + " " + err.__str__())
        """
        "Невозможно открыть указанную страницу {0}.\n" \
        "Пожалуйста, проверьте соединение с интернетом.".format(page)
        """


def CheckLinksFromPage(url, startURL):
    request = urllib2.Request(url)

    try:
        response = urllib2.urlopen(request)
    except BaseException as err:
        return False
    else:
        usedUrls.append(url)

        content = response.read()

        # Find address data
        '''
        Атрибут href может содержать:
        Абсолютный URL — адрес страницы, документа или скрипта. Это наиболее распространенный вариант.
        Относительный URL — адрес страницы, документа или скрипта
        mailto: — e-mail адрес. Для написания письма откроется системный e-mail клиент.
        javascript: — исполняемый скрипт
        skype: — вызов абонента skype
        # — локальная ссылка(якорь)
        '''
        dataAllUrls = re.findall('href="((http|ftp)?.*?)"', content)
        dataUrls = re.findall('href="(((http|ftp)s?://)?.*?(/.*?)*)"', content)
        dataUrls2 = []
        for data in dataUrls:
            needDelete = False
            for element in {"mailto:", "javascript:", "skype:", "#"}:
                #print data[0][:len(element)]
                if element == data[0][:len(element)]:
                    #print element != data[0][len(element):]
                    needDelete = True
            if not needDelete:
                dataUrls2.append(data)

        # Conversion in absolute address
        convertAllDataUrls = [urlparse.urljoin(url, urlI[0]) for urlI in dataAllUrls]
        convertDataUrls = [urlparse.urljoin(url, urlI[0]) for urlI in dataUrls2]

        for urlList in convertDataUrls:
            if (not (urlList in usedUrls) and not (urlList in queuedURLS) and
                    (-1 != urlList.find(startURL, 0, len(urlList))) ):  # не выходим за рамки этого сайта
                queuedURLS.append(urlList)
            if( not (urlList in usedUrls)):
                usedUrls.append(urlList)

        for urlList in convertAllDataUrls:
            if ( (urlList not in convertDataUrls) ):  # не выходим за рамки этого сайта
                listOtherRef.append(urlList)
            #if( not (urlList in usedUrls)):
            #   usedUrls.append(urlList)



def CheckLinks(urls):
    for url in urls:
        CheckReference(url)
        del url

def deleteWhitespaceInEnd(url):
    result = url
    for char in url:
        if char == ' ':
            result = url[:-1]

    return result

# /////////////////////////////////////////////#
# \/               Main                     \/ #
def MainFunction(argv, startURL):
    if (len(sys.argv) != 2):
        queuedURL = raw_input("Print address page as parametr.\n"
                              "Format entering: link_checker.exe http://path-to-site.com.\n"
                              "Enter URL: ")

        """
        "Укажите адрес страницы в качестве параметра.\n"
        "Формат ввода link_checker.exe http://path-to-site.com.\n"
        "Введите URL: "
        """
    else:
        queuedURL = argv[1]


    isErrorInURL = True
    queuedURL = deleteWhitespaceInEnd(queuedURL)
    startURL = queuedURL
    queuedURLS.append(queuedURL)
    while (len(queuedURLS)):
        try:
            CheckLinksFromPage(queuedURLS[0], startURL)
            CheckLinks(usedUrls)
            isErrorInURL = False
        except (urllib2.URLError, ValueError) as err:
            queuedURL = raw_input("Print address page as parametr.\n"
                                  "Format entering: link_checker.exe http://path-to-site.com.\n"
                                  "Enter URL: ")
        del queuedURLS[0]

    if isErrorInURL == False:
        if len(usedUrls):
            del usedUrls[0]

            CheckLinks(usedUrls)

        allRef = open("AllReference.txt", 'w')
        for url in correctUrls:
            allRef.write(url + '\n')
        for url in listOtherRef:
            allRef.write(url + '\n')
        for url in failedUrl:
            allRef.write(url + '\n')
        allRef.close()

        incorrectRef = open("InvalidReference.txt", 'w')

        for url in failedUrl:
            incorrectRef.write(url + '\n')
        incorrectRef.close()

    print ("Program executed")
# /////////////////////////////////////////////#
# http://bochtest.blogspot.ru/
# http://links.testingcourse.ru
MainFunction(sys.argv, startURL)