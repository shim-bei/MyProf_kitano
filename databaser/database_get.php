<!-- 一番新しいデータだけを取り出したい -->

<?php
$conn = new mysqli('host', 'username', 'database-name', 'password');

// データを取得
$sql = "SELECT id, maguro, uni, ebi, tamago, ikura, ika FROM sushineta";
$result = $conn->query($sql);
// 現在時刻をユニックスタイムで取得し、データ量削減のために上２桁を削る
$time=time();
$time = substr($time, 3,10);

// データを出力
if ($result->num_rows > 0) {
    // 出力データを配列に格納
    $output = array();
    while($row = $result->fetch_assoc()) {
        $output[] = $row;
        
        //現在の時刻とデータベースに書き込まれた時刻の差をとる         
        $diff = $time - $row['nowtime'];
        //データベースに格納されてから一定時間がたっていればデータを消去
        if($diff > 72000){
            $sqld = "DELETE FROM sushineta";
            // SQL文を実行
            mysqli_query($conn, $sqld);    
        }
    }

    // JSON形式で出力
    echo json_encode($output);
} else {
    echo "0 results";
}

// データベース接続を閉じる
$conn->close();
?>
