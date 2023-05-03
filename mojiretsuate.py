import re
#任意の４文字の単語　ここでは私のあだ名をチョイスしています！
ques = "しんべえ"
F_light = 0

while F_light != 1:
  hit = 0
  nhit = 0
  incur = 0
  p = re.compile('[\u3041-\u309F]+')
  ans = input("ひらがな４文字の単語を入力してください：")

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

  if ques == ans:
    print("That's Light Ishimatsu!")
    F_light = 1
  else:
    for y in range(4):
      for x in range(4):
        if ans[:y] == ques[:x]:
          hit += 1
    for c in ans:
      #inputで受け取った文字列（ans）を配列で認識し、既定の文字列と同じ文字が含まれていたら変数を+1する
        if c in ques:
            nhit += 1
    print(str(hit - 1) + "文字、場所があってるで")
    print(str(nhit) + "文字含まれてるのはあってるで")