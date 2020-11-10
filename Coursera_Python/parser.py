import requests
from bs4 import BeautifulSoup
import csv
import os

URL =  'https://auto.ria.com/uk/legkovie/'#'https://auto.ria.com/uk/newauto/marka-jeep/'
HEADERS = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.83 Safari/537.36', 'accept': '*/*'}
HOST = 'https://auto.ria.com'
FILE ='cars.csv'



def  get_html(url, params =None):
    r = requests.get(url,headers =HEADERS, params =params)
    return r

def save_file(items, path):
    with open(path,'w',newline='') as file :
        write =csv.writer(file, delimiter=';')
        write.writerow(['Марка', 'Посилання' , ' ціна в $' , 'ціна в грн', 'місто'])
        for item in items :
            write.writerow([item['title'], item['link'],item['usd price'], item['uah price'], item['city']])

def get_pages_count (html):
    soup = BeautifulSoup(html, 'html.parser')
    pagination = soup.find_all('span', class_= 'page-item mhide')
    if pagination:
        page = pagination[-1].get_text()
        page = page.strip()
        LeN =len(page)
        return  int(page)
    else:
        return 1


def get_content(html):
    soup = BeautifulSoup(html, 'html.parser')
    items = soup.find_all(class_ = 'proposition_area')
    cars = []
   # print(items)
    for item in items:
        uah_price = item.find('span', class_= 'grey size13')
        if uah_price:
            uah_price = uah_price.get_text(strip = True)
        else:
            uah_price = 'цену утоняйте'
        cars.append({
            'title': item.find('strong').get_text(strip = True),
            'link': HOST + item.find('a').get('href'),
            'usd price': item.find('span', class_= 'green bold size18').get_text(strip = True),
            'uah price': uah_price,
            'city' : item.find('svg' ,class_ = 'svg svg-i16_pin' ).find_next('strong').get_text()
        })
    return cars


def parse():
    # URL = input('введіть url:')
    # URL = URL.strip()
    html =get_html(URL)

    if html.status_code == 200:
        cars =[]
        get_pages = get_pages_count(html.text)
        for page in range(1,get_pages+1):
            print(f'парсинг сторинки {page} з {get_pages}...')
            html = get_html(URL,params={'page': page})
            cars.extend(get_content(html.text))
        save_file(cars,FILE)

        print(f'отримано  {len(cars)} елементів')
        os.startfile(FILE)
    else:
        print('Error')

parse()
