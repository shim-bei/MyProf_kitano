#モジュールの呼び出し
import re

#変数の定義
#任意の４文字の単語　ここでは私のあだ名をチョイスしています！
ques = "しんべえ"
F_light = 0

#正解が出るまで繰り返す
while F_light != 1:
  #変数を毎回初期化
  hit = 0
  nhit = 0
  incur = 0
  #ひらがなの文字コードを格納
  p = re.compile('[\u3041-\u309F]+')
  #適当な４文字の入力を受ける
  ans = input("ひらがな４文字の単語を入力してください：")

  #４文字でない、ひらがな以外が含まれている、２回以上おなじ文字が使われている場合はう一度入力
  if(len(ans) != 4):
    print("それは４文字とちゃうで")
    continue
  if not p.fullmatch(ans):
    print("ひらがなとちゃう文字が入っとるがな。")
    continue
  for char in ans:
      if ans.count(char) >= 2:
        print("同じ文字が含まれとるやぁないか") 
        incur = 1
        break
  if incur == 1:
    continue

  #もしあっていれば正解を伝え、ループを抜ける
  if ques == ans:
    print("That's Light Ishimatsu!")
    F_light = 1
  #そうでなければ
  else:
    #文字の場所があっていれば変数を+1していく
    for y in range(4):
      for x in range(4):
        if ans[:y] == ques[:x]:
          hit += 1
    for c in ans:
      #inputで受け取った文字列（ans）を配列で認識し、既定の文字列と同じ文字が含まれていたら変数を+1する
        if c in ques:
            nhit += 1
      #文字数をそれぞれ表示
    print(str(hit - 1) + "文字、場所があってるで")
    print(str(nhit) + "文字含まれてるのはあってるで")
