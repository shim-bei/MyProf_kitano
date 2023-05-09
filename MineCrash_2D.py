#モジュールのインポート
import random
import math
import tkinter
import tkinter.messagebox as messagebox

#ゲーム画面の作成
version = tkinter.Tcl().eval('info patchlevel')
window = tkinter.Tk()
window.geometry("1000x1000")
window.title("画像表示：" + version)
 
canvas = tkinter.Canvas(window, bg = "#deb887", height = 1000, width = 1000)
canvas.place(x = 0, y = 0)

#画像とステージの大きさの決定
imagesize = 150
stagesize_x = 5
stagesize_y = 5

#画像（プレイヤーとステージ）の読み込み
Stage = tkinter.PhotoImage(file = "Stage.png", width = imagesize, height = imagesize)
Miritary = tkinter.PhotoImage(file = "miritari-.png", width = imagesize, height = imagesize)

#変数の初期化
txt = ""
direct = ""
ansx = random.randint(0,stagesize_x - 1)
ansy = random.randint(0,stagesize_y - 1)
xin = random.randint(0,stagesize_x - 1)
yin = random.randint(0,stagesize_y - 1)
posx = xin
posy = yin

#送信ボタンを押された時の処理
def btn_click():
  global direct
  global txtcheck  
  #入力された文字列をdirectに格納する
  direct = txt.get()
  txtcheck = 1
  print(txtcheck)
  txt.delete(0, tkinter.END)
  
#画面の継続的な描画
def loopWindow():
    global xin
    global yin
    global posx
    global posy
    global direct
    
    #directに文字列が格納されていた場合の処理（移動もしくはダイアログボックスの表示）
    if direct != "":
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
                messagebox.showinfo('朗報　除去成功', '処理が完了しました。')
                window.destroy()
            else:
                messagebox.showinfo('除去失敗のお知らせ', 'MINE IS FINE.\nFIND IT!')
        elif direct == "search":
            messagebox.showinfo('調査完了のお知らせ',"地雷との距離は" + str(math.sqrt((xin - ansx)*(xin - ansx)+(yin - ansy)*(yin - ansy))) + "だ")
        else:
            messagebox.showinfo('間違いのお知らせ', 'その文字列には非対応です\na, d, w, s, searchもしくはcrashのいずれかを入力してください')
        
        #もし画面外に移動したら描画する前にプレイヤーを元の座標に戻す
        if posx >= stagesize_x or posy >= stagesize_y or posx < 0 or posy < 0:
            messagebox.showinfo('間違いのお知らせ', '捜索範囲外です')
            posx = xin
            posy = yin
        else:
            xin = posx
            yin = posy
        #directを初期化
        direct = ""
    
    #画面をクリアした後ステージとプレイヤーを再描画
    canvas.delete("all")
    for y in range(stagesize_y):
        for x in range(stagesize_x):
            if (x,y) == (xin,yin):
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Miritary, anchor = tkinter.NW)
            else:
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)  
    window.after(50, loopWindow)

#文字が入力された時の処理
def checker(event):
    global direct
    direct = txt.get()
    if direct != "":
        txt.delete(0, tkinter.END)

#"What Will You Do？"ラベルの表示
lbl = tkinter.Label(text='What will you do?')
lbl.place(x=300, y=10)
txt = tkinter.Entry(width=10)
txt.place(x = 445, y = 10)

#関数の実施
loopWindow()   
window.bind("<Return>", checker)

window.mainloop()

