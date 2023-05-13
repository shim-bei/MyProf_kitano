<?php
// 入力確認
$Id = $_POST['id'];
$Id = mb_convert_encoding($Id, "UTF-8");

$maguro = $_POST['maguro'];
$maguro = mb_convert_encoding($maguro, "UTF-8");

$uni = $_POST['uni'];
$uni = mb_convert_encoding($uni, "UTF-8");

$ebi = $_POST['ebi'];
$ebi = mb_convert_encoding($ebi, "UTF-8");

$tamago = $_POST['tamago'];
$tamago = mb_convert_encoding($tamago, "UTF-8");

$ikura = $_POST['ikura'];
$ikura = mb_convert_encoding($ikura, "UTF-8");

$ika = $_POST['ika'];
$ika = mb_convert_encoding($ika, "UTF-8");

if (empty($Id))
{
echo '<p>投稿に失敗しました</p>';
echo '<p>ERROR : コメントが空白です</p>';
exit();
}

// DBに接続　






//以下データベースとの接続
$mysqli = new mysqli('', '', '', '');

// 接続結果の確認 エラーがあればエラー文を表示
if (mysqli_connect_errno())
{
echo '<p>投稿に失敗しました</p>';
echo '<p>ERROR : データベースへの接続に失敗しました</p>';
exit();
}

// レコード取得のSQL作成（最大件数を超える場合は投稿を許可しない）
$sql = "SELECT * FROM sushineta";

// SQL実行
$result = $mysqli->query($sql);

// 実行結果確認 $maxは定数で$numは変数
$max = 50;
$num = $max;
if ($result)
{
$num = $result->num_rows;
}
if (!$result )
{
echo '<p>投稿に失敗しました</p>';
$mysqli->close();
exit();
}
if ($num >= $max)
{
echo '<p>ERROR : データベースの保存件数が最大です</p>'. $mysqli->error;
$mysqli->close();
exit();    
}

// 投稿データ追加のSQL文(insert)作成
$sql = "INSERT INTO sushineta (date, id, maguro, uni, ebi, tamago, ikura, ika) VALUES ('".date('Y-m-d H:i:s')."',
                                 '".$Id."', '".$maguro."', '".$uni."', '".$ebi."', '".$tamago."', '".$ikura."', '".$ika."')";

// SQL実行
$result = $mysqli->query($sql);

// 切断
$mysqli->close();

// 元のページにリダイレクト
header("Location: http://sushin.php.xdomain.jp/Info_Kitano.html");
exit();
?>
