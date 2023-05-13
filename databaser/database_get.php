<!-- 一番新しいデータだけを取り出したい -->

<?php
$conn = new mysqli('host', 'username', 'database-name', 'password');

// データを取得
$sql = "SELECT id, maguro, uni, ebi, tamago, ikura, ika FROM sushineta";
$result = $conn->query($sql);

// データを出力
if ($result->num_rows > 0) {
    // 出力データを配列に格納
    $output = array();
    while($row = $result->fetch_assoc()) {
        $output[] = $row;
    }

    // JSON形式で出力
    echo json_encode($output);
} else {
    echo "0 results";
}

// データベース接続を閉じる
$conn->close();
?>