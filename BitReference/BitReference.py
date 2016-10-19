# coding=utf-8
import sys
import re, urllib, urllib2, urlparse

usedUrls = []
correctUrls = []
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

        status = str(code)
        if (code not in [200, 301]):
            failedUrl.append(page + " " + status)
            # print message if not internet
        else:
            correctUrls.append(page + " " + status)

    except BaseException as err:
        # print("IOError error: {0}".format(err))
        print "Невозможно открыть указанную страницу {0}.\n" \
              "Пожалуйста, проверьте соединение с интернетом.".format(page)
        exit()


def CheckLinksFromPage(url):

    if not (url in usedUrls):
        request = urllib2.Request(url)

        try:
            response = urllib2.urlopen(request)
        except BaseException as err:
            print "Невозможно открыть указанную страницу {0}.\n" \
                  "Пожалуйста, проверьте соединение с интернетом.".format(url)
        else:
            usedUrls.append(url)


            content = response.read()

            # Find address data
            dataUrls = re.findall('href="(.*?)"', content)

            # Conversion in absolute address
            convertDataUrls = [urlparse.urljoin(url, urlI) for urlI in dataUrls]

            for urlList in convertDataUrls:
                if( not (usedUrls in convertDataUrls)):
                    usedUrls.append(urlList)


def CheckLinks(urls):
    for url in urls:
        CheckReference(url)

# /////////////////////////////////////////////#
# \/              Main                     \/ #
def MainFunction(argv):
    if (len(sys.argv) != 2):
        queuedURL = raw_input("Укажите адрес страницы в качестве параметра.\n"
                              "Формат ввода link_checker.exe http://path-to-site.com.\n"
                              "Введите URL: ")
    else:
        queuedURL = argv[1]

    isErrorInURL = True
    while (isErrorInURL):
        try:
            CheckLinksFromPage(queuedURL)
            break
        except (urllib2.URLError, ValueError) as err:
            queuedURL = raw_input("Введенный адрес не является корректным URL.\n"
                                  "Пожалуйста, введите адрес в формате http://path-to-site.com\n"
                                  "Введите URL: ")
            continue

    del usedUrls[0]
    CheckLinks(usedUrls)

    correctRef = open("AllReference.txt", 'w')
    for url in correctUrls:
        correctRef.write(url + '\n')
    correctRef.close()

    incorrectRef = open("InvalidRefernce.txt", 'w')
    for url in failedUrl:
        incorrectRef.write(url + '\n')
    incorrectRef.close()

    print ("Program executed")
# /////////////////////////////////////////////#

MainFunction(sys.argv)