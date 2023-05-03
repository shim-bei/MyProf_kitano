import random
import math

stagesize_x = 5
stagesize_y = 5

flag = 0
ansx = random.randint(0,stagesize_x - 1)
ansy = random.randint(0,stagesize_y - 1)
xin = random.randint(0,stagesize_x - 1)
yin = random.randint(0,stagesize_y - 1)
posx = xin
posy = yin

while flag == 0:
  for y in range(stagesize_y):
      for x in range(stagesize_x):
          if (x,y) == (xin,yin):
                  print("〇" , end = "")
          else:
               print("・" , end = "")
      print("")

  direct = input("WHAT WILL YOU DO ?:")
  if direct == "a":
    posx -= 1
  elif direct == "d":
    posx += 1
  elif direct == "s":
    posy += 1
  elif direct == "w":
    posy -= 1
  elif direct == "crash":
    if (xin,yin) == (ansx,ansy):
      print("MINE CRASHED!")
      flag = 1
    else:
      print("MINE IS FINE")
      print("FIND IT!")
      print("")
  elif direct == "search":
      print("地雷との距離は" + str(math.sqrt((xin - ansx)*(xin - ansx)+(yin - ansy)*(yin - ansy))) + "だ")
  else:
    print("IT'S WRONG")

  if posx >= stagesize_x or posy >= stagesize_y or posx < 0 or posy < 0:
      print("はみでるがなあ")
      posx = xin
      posy = yin
      continue 
  else:
    xin = posx
    yin = posy