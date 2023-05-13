import json
import requests
import time
import tkinter
import tkinter.messagebox as messagebox

# 参照元のPHPファイルのURLを格納
url = "http://sushin.php.xdomain.jp/pytest.php"

# Tkinterの初期設定 
version = tkinter.Tcl().eval('info patchlevel')
window = tkinter.Tk()
window.geometry("1000x1000")
window.title("画像表示：" + version)
canvas = tkinter.Canvas(window, bg = "#deb887", height = 1000, width = 1000)
canvas.place(x = 0, y = 0)

# 背景画像の設定
imagesize = 150
BackGround = tkinter.PhotoImage(file = "MineCrash/Stage.png", width = imagesize, height = imagesize)

txt = ""
getID = ""
tyumon = {}

# 入力された値によって行う動作　ここが今後の課題
def maguro_one():
    print(maguro)
    
def maguro_two():
    print(maguro+2)
    
def uni_one():
    print(uni)
    
def uni_two():
    print(uni + 2)
    
def ebi_one():
    print(ebi)
    
def ebi_two():
    print(ebi + 2)
    
def ikura_one():
    print(ikura)
    
def ikura_two():
    print(ikura + 2)
    
def tamago_one():
    print(tamago)
    
def tamago_two():
    print(tamago + 2)
    
def ika_one():
    print(ika)
    
def ika_two():
    print(ika + 2)
    

# ハンドの動作の準備
def MoveCheck():
    # for key , balues in tyumon.items():
    #     if key != "nowtime" and key != "id":
    #         # ここで各ネタの注文数を各変数に格納できている（！！）
    #         key = balues
    #         if(maguro != 0)
    if maguro != 0:
        print("まぐろ：")
        if maguro == 1:
            maguro_one()
        elif maguro==2:
            maguro_two()
            
    if uni != 0:
        print("うに：")
        if uni == 1:
            uni_one()
        elif uni==2:
            uni_two()
            
    if ebi != 0:
        print("えび：")
        if ebi == 1:
            ebi_one()
        elif ebi==2:
            ebi_two()
            
    if ikura != 0:
        print("いくら：")
        if ikura == 1:
            ikura_one()
        elif ikura==2:
            ikura_two()
            
    if tamago != 0:
        print("たまご：")
        if tamago == 1:
            tamago_one()
        elif tamago==2:
            tamago_two()
            
    if ika != 0:
        print("いか：")
        if ika == 1:
            ika_one()
        elif ika==2:
            ika_two()
    
  
#   一定周期で入力を確認する
def loopWindow():
    global getID
    global tyumon
    global maguro
    global uni
    global ebi
    global ikura
    global tamago
    global ika
    waiter = 0
    
    #IDが入力されていて、ハンドの動作が終了していれば     
    if getID != "" and waiter == 0:    
        #phpに接続する
        response = requests.get(url)

        # PHPからデータベースの情報をJSONデータで受け取る
        data = json.loads(response.text)

        #現在時刻をタイムスタンプで取得し、データ削減ため、上２桁を削る
        pytime = str(int(time.time()))
        pytime = pytime[-7:]
        pytime = int(pytime)

        tyumon = ""
        table_lenth = len(data)
        
        # idのチェックと時間以内の判定
        for x in range(table_lenth):
            nowtime = int(data[x]["nowtime"])
            if((pytime - nowtime) < 72000):
                # 入力されたidと同じidがあればその配列を専用の配列に格納しなおす
                if(getID == data[x]["id"]):
                    tyumon = data[x]
                    break                

        #IDがデータベースになければエラー文を吐く、あればFlagを立てる
        if(not tyumon):
            messagebox.showinfo('anything else', 'idが間違っているか、注文が完了していない\nもしくは注文が古すぎます')
            ID_check = 0
        else:
            ID_check = 1

            
        # 上のフラッグを参照する。IDがあれば格納されている値を全て変数に入れ直し、メッセージボックスを表示
        if ID_check == 1:
            maguro = int(tyumon["maguro"])
            uni = int(tyumon["uni"])
            ebi = int(tyumon["ebi"])
            ikura = int(tyumon["ikura"])
            tamago = int(tyumon["tamago"])
            ika = int(tyumon["ika"])
            
            # メッセージボックスの生成
            messagebox.showinfo('注文内容の確認',
                                "注文内容は以下の通りです\nマグロ：%d貫\nウニ：　%d貫\nエビ：　%d貫\nイクラ：%d貫\n玉子：　%d貫\nイカ：　%d貫\n"
                                % (maguro, uni, ebi, ikura, tamago, ika))
       
        # tyumonに情報が格納された状態で、今度はハンドの動作を行う
        if getID != "" and ID_check == 1:
            waiter = 1
            MoveCheck()
            waiter = 0
        
        # 格納したIDを廃棄
        getID = ""
    window.after(500, loopWindow)



# Enterが押された時の処理
def checker():
    global getID
    getID = txt.get()
    if getID != "":
        txt.delete(0, tkinter.END)
        
# ENTERが押された時の処理を１つにまとめる（バグ防止）
def ENTER_HIT(event):
    checker()

# Tkinter画面のテキストボックスの設定
# canvas.create_image(30 + imagesize, 30 + imagesize, image = BackGround, anchor = tkinter.NW)
lbl = tkinter.Label(text='あなたのIDを教えて下さい', width = 100, height = 40)
lbl.place(x=200, y=100)
txt = tkinter.Entry(width = 100)
txt.place(x = 400, y = 440)

# 自作のループ関数を１度呼び出す
loopWindow()

# Enterキーが押されたらcheckerという自作関数を呼ぶ
window.bind("<Return>", ENTER_HIT)

# 閉じられるまで永遠にループ
window.mainloop()

