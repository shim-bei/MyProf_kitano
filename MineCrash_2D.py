import random
import math
import tkinter
import tkinter.messagebox as messagebox

version = tkinter.Tcl().eval('info patchlevel')
window = tkinter.Tk()
window.geometry("1000x1000")
window.title("画像表示：" + version)
 
canvas = tkinter.Canvas(window, bg = "#deb887", height = 1000, width = 1000)
canvas.place(x = 0, y = 0)

imagesize = 150

Stage = tkinter.PhotoImage(file = "Stage.png", width = imagesize, height = imagesize)
Miritary = tkinter.PhotoImage(file = "miritari-.png", width = imagesize, height = imagesize)

stagesize_x = 5
stagesize_y = 5
txt = ""
direct = ""
ansx = random.randint(0,stagesize_x - 1)
ansy = random.randint(0,stagesize_y - 1)
xin = random.randint(0,stagesize_x - 1)
yin = random.randint(0,stagesize_y - 1)
posx = xin
posy = yin


def btn_click():
  global direct
  global txtcheck
  direct = txt.get()
  txtcheck = 1
  print(txtcheck)
  txt.delete(0, tkinter.END)
  print(direct)
  
def loopWindow():
    global xin
    global yin
    global posx
    global posy
    global direct
    
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
        if posx >= stagesize_x or posy >= stagesize_y or posx < 0 or posy < 0:
            messagebox.showinfo('間違いのお知らせ', '捜索範囲外です')
            posx = xin
            posy = yin
        else:
            xin = posx
            yin = posy
        direct = ""
    
    #print(xin,yin)
    canvas.delete("all")
    for y in range(stagesize_y):
        for x in range(stagesize_x):
            if (x,y) == (xin,yin):
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Miritary, anchor = tkinter.NW)
            else:
                canvas.create_image(30 + x * imagesize, 30 + y * imagesize, image = Stage, anchor = tkinter.NW)  
    if posx >= stagesize_x or posy >= stagesize_y or posx < 0 or posy < 0:
        posx = xin
        posy = yin
    else:
        xin = posx
        yin = posy

    window.after(50, loopWindow)

def checker(event):
    global direct
    direct = txt.get()
    if direct != "":
        txt.delete(0, tkinter.END)

lbl = tkinter.Label(text='What will you do?')
lbl.place(x=300, y=10)
txt = tkinter.Entry(width=10)
txt.place(x = 445, y = 10)

loopWindow()   
window.bind("<Return>", checker)

window.mainloop()

