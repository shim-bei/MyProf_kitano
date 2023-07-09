import random
import math
import tkinter
import tkinter.messagebox as messagebox
import time

#Tkinterの画面の初期化
version = tkinter.Tcl().eval('info patchlevel')
window = tkinter.Tk()
window.geometry("1000x1000")
window.title("Mine Crash") 
canvas = tkinter.Canvas(window, bg = "#deb887", height = 1000, width = 1000)
canvas.place(x = 0, y = 0)

# 画面サイズの定義
imagesize = 150 #サイズの変更は出来ません
stagesize_x = 5 #サイズの変更は出来ません
stagesize_y = 5 #サイズの変更は出来ません

# 画像を読み込む
Stage = tkinter.PhotoImage(file = "Stage.png", width = imagesize, height = imagesize)
Miritary = tkinter.PhotoImage(file = "miritari-.png", width = imagesize, height = imagesize)

# プレイヤーの初期座標と地雷の座標をランダムに設定
ansx = random.randint(0,stagesize_x - 1)
ansy = random.randint(0,stagesize_y - 1)
xin = random.randint(0,stagesize_x - 1)
yin = random.randint(0,stagesize_y - 1)

# 必要な変数を初期化
txt = ""
direct = ""
posx = xin
posy = yin
bomb = 0

nowTime = 0
setTime = str(int(time.time()))
setTime = setTime[-7:]
setTime = int(setTime)

Limit = nowTime - setTime

# Tkinterのラベルを作成する
lbl = tkinter.Label(text='What will you do?', width=0,height=0, font = ('UD デジタル 教科書体 NP-B',16))
lbl.place(x=200, y=10, width = 200, height = 20)
txt = tkinter.Entry(width = 10)
txt.place(x = 450, y = 10)

# 「距離を測る」ボタンを押されたら、地雷との距離をメッセージボックスで表示
def Search():
    messagebox.showinfo('調査完了のお知らせ',"地雷との距離は" + 
                        str(math.sqrt((xin - ansx)*(xin - ansx)+(yin - ansy)*(yin - ansy))) + "だ")

# 「地雷をCrash！」ボタンを押されたら地雷があるかを判定する
def Crash():
    global bomb
    # もしあればメッセージボックスを表示して画面を閉じる
    if (xin,yin) == (ansx,ansy):
        bomb = 1
        messagebox.showinfo('朗報　除去成功', '処理が完了しました。')
        window.destroy()
    # なければメッセージボックスを表示して再開する
    else:
        messagebox.showinfo('除去失敗のお知らせ', 'MINE IS FINE.\nFIND IT!')

# 「距離を測る」ボタンの基本設定
check_button = tkinter.Button(window,text="距離を測る", width = 10, height = 3, font = ('UD デジタル 教科書体 NP-B',14),
                                bg = "light coral", relief = "raised", bd = 14, 
                              command = Search)

check_button.place(x = 840, y =150 )

# 「地雷をCrash！」ボタンの基本設定
crash_button = tkinter.Button(window,text="地雷をCrash！", width = 12, height = 3, font = ('UD デジタル 教科書体 NP-B',14),
                                bg = "pale turquoise", relief = "raised", bd = 14, 
                              command = Crash)

crash_button.place(x = 820, y =400 )

#制限時間を設定する
def TimeOver():
    global bomb
    if Limit < 0 and bomb == 0 :
        messagebox.showinfo('TIMEOVER', '判断が遅い！')
        window.destroy() 

    
# 画面のループ処理　whileの代わり
def loopWindow():
    global xin
    global yin
    global posx
    global posy
    global direct
    global setTime
    global Limit
    global bomb
    
    # 制限時間の設定
    TimeLimit = 5
    
    # 現在時間をタイムスタンプを用いて取得する
    nowTime = str(int(time.time()))
    nowTime = nowTime[-7:]
    nowTime = int(nowTime)
    
    #開始時間からの経過時間を取得する　＝　残り時間
    if bomb == 0:
        Limit = TimeLimit -( nowTime - setTime )
    
    TimeOver()
    
    # 制限時間のラベルの初期設定
    lbl = tkinter.Label(text=Limit, width = 4, height = 2, font = ('ゴシック',30),
                                bg = "white", relief = "raised", bd = 5)
    lbl.place(x=780
              , y=30)

    
    # 入力された文字を調べる
    # 「a」、「d」、「w」、「s」でそれぞれ左右、上下の仮想的な座標変数を１だけ変更する
    if direct != "":
        if direct == "a":
            posx -= 1
        elif direct == "d":
            posx += 1
        elif direct == "s":
            posy += 1
        elif direct == "w":
            posy -= 1
        
        # もし上記の文字列以外であればメッセージボックスを表示する
        else:
            messagebox.showinfo('間違いのお知らせ', 'その文字列には非対応です\na, d, w, s, searchもしくはcrashのいずれかを入力してください')
        
        # もしプレイヤーが画面外の座標に移動したらメッセージボックスを表示し、実際の座標に仮想的な座標変数を代入しない
        if posx >= stagesize_x or posy >= stagesize_y or posx < 0 or posy < 0:
            messagebox.showinfo('間違いのお知らせ', '捜索範囲外です')
            posx = xin
            posy = yin
            
        # プレイヤーが画面内を移動している場合は、仮想的な変数を実際の座標に反映する
        else:
            xin = posx
            yin = posy
            
        # 文字列を空にして入力を待つ
        direct = ""
        
    # 画面の描画をし直すため、画面を全消去する
    canvas.delete("all")
    
    # ５×５を１マスずつ描画する
    for y in range(stagesize_y):
        for x in range(stagesize_x):
            # もしプレイヤーの座標だったらプレイヤーの画像を上書きする
            if (x,y) == (xin,yin):
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Miritary, anchor = tkinter.NW)
            # そうでなければ背景を描くのみ
            else:
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)  
    
    # 描画しなおす間隔を設定する（Frame Per Secondのようなもの）
    window.after(50, loopWindow)

# Enterキーが押されたときの関数
def checker(event):
    global direct
    # 入力された文字を変数に代入する
    direct = txt.get()
    # もし入力されたらテキストボックス内の文字を取り除く
    if direct != "":
        txt.delete(0, tkinter.END)

# 前述の関数を実行する
loopWindow()   

# Enterキーが押されたらchackerという関数を実行する
window.bind("<Return>", checker)

window.mainloop()

