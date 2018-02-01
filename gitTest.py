import requests

url = 'http://www.baidu.com'

headers = {
	'User-Agent': 'git-test'
}

response = requests.get(url, headers = headers)