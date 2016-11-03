# coding=utf-8
import sys, lxml.html
import re, urllib, urllib2, urlparse

usedUrls = []
startURL = ""
correctUrls = []
urlsForCheck = []
failedUrl = []
queuedURL = ""
queuedURLS = []

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
        if (code not in [200, 301]):
            if (page + " " + status) not in failedUrl:
                failedUrl.append(page + " " + status)
            # print message if not internet
        else:
            if (page + " " + status) not in correctUrls:
                correctUrls.append(page + " " + status)
                urlsForCheck.append(page)

    except BaseException as err:
        # print("IOError error: {0}".format(err))
        print "Imposible open the page {0}.\n" \
              "Please, check conect with internet.".format(page)

        if (page + " " + err.__str__()) not in failedUrl:
            failedUrl.append(page + " " + err.__str__())
        """
        "Невозможно открыть указанную страницу {0}.\n" \
        "Пожалуйста, проверьте соединение с интернетом.".format(page)
        """
        #exit()


def CheckLinksFromPage(url, startURL):

    #if not (url in usedUrls):
    request = urllib2.Request(url)

    try:
        response = urllib2.urlopen(request)
    except BaseException as err:
        print "Imposible open the page {0}.\n" \
                "Please, check conect with internet.".format(url)
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
        #dataUrls = re.findall('"((http|ftp)s?://.*?)"', content)

        # Conversion in absolute address
        convertDataUrls = [urlparse.urljoin(url, urlI[0]) for urlI in dataUrls2]

        startURL2 = startURL
        for urlList in convertDataUrls:
            if (not (urlList in usedUrls) and not (urlList in queuedURLS) and
                    (-1 != urlList.find(startURL, 0, len(urlList))) ):  # не выходим за рамки этого сайта
                queuedURLS.append(urlList)
            if( not (urlList in usedUrls)):
                usedUrls.append(urlList)


        return True
        #return False


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

def DeleteNotWebPage(urls):
    for url in urls:
        for element in {".htm", ".html"}:# TODO : не обрабатывает пустые ссылки
            # print data[0][:len(element)]
            if element != url[:len(element)]:
                del url
                break

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

    global pageOpen
    pageOpen = False
    isErrorInURL = True
    queuedURL = deleteWhitespaceInEnd(queuedURL)
    startURL = queuedURL
    queuedURLS.append(queuedURL)
    while (len(queuedURLS)):
        #del usedUrls
        #if (not (queuedURLS[0] in usedUrls)):
        try:
            pageOpen = CheckLinksFromPage(queuedURLS[0], startURL)
            CheckLinks(usedUrls)
            #usedUrls = []
            '''
            ####################################
            # Delete reference is'nt web-page
            urlsForCheck = correctUrls
            DeleteNotWebPage(urlsForCheck)
            # Check page the sait
            for urlElement in urlsForCheck:
                CheckLinksFromPage(urlElement)
                CheckLinks(usedUrls)
            ####################################
            '''


            isErrorInURL = False
        except (urllib2.URLError, ValueError) as err:
            queuedURL = raw_input("Print address page as parametr.\n"
                                  "Format entering: link_checker.exe http://path-to-site.com.\n"
                                  "Enter URL: ")
            #continue
        del queuedURLS[0]

    if isErrorInURL == False:
        if len(usedUrls):
            del usedUrls[0]

            CheckLinks(usedUrls)

        #if pageOpen:

        correctRef = open("AllReference.txt", 'w')
        for url in correctUrls:
            correctRef.write(url + '\n')
        correctRef.close()

        incorrectRef = open("InvalidReference.txt", 'w')
        for url in failedUrl:
            incorrectRef.write(url + '\n')
        incorrectRef.close()

    print ("Program executed")
# /////////////////////////////////////////////#
# http://bochtest.blogspot.ru/
# http://links.testingcourse.ru
MainFunction(sys.argv, startURL)