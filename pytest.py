import json
import requests

url = "http://sushin.php.xdomain.jp/pytest.php"

# 一定周期でphpに接続する
response = requests.get(url)

data = json.loads(response.text)
print(data)

# idの識別
# 入力されたidと同じidがあればその配列を専用の配列に格納しなおす

#なければエラー文を吐く 


# 各変数の識別
# 格納されている値を全て確認し、Flagを立てる

# 立ったフラッグに従って機械を動かす