<?php
$connection = new mysqli("localhost", "daltonjn_school", "CMUNETworks", "daltonjn_school");
$sql = "SELECT * FROM detection ORDER BY id DESC";
$result = $connection->query($sql);
while($row = $result->fetch_assoc()){
	echo "<p style='padding:0px; margin: 0px; font-size: 8pt;'>ID:{$row['id']} | YEAR:{$row['year']} | MONTH:{$row['month']} | DAY:{$row['day']} | HOUR:{$row['hour']} | MINUTE:{$row['minute']} | SECOND:{$row['second']} </p>";
}
?>


<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Detection Log</title>
<script>
	function wait(){
		window.setTimeout(reload, 5000);
	}
	function reload(){
		location.reload();
	}
</script>
</head>

<body onLoad="wait()">
</body>
</html>