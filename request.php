<?php
$connection = new mysqli("localhost", "daltonjn_school", "CMUNETworks", "daltonjn_school");
if(isset($_GET['token'])){
	if($_GET['token'] = "CMUNetworksClass"){
		$sql = "INSERT INTO detection (year, month, day, hour, minute, second) VALUES ('{$_GET['year']}', '{$_GET['month']}', '{$_GET['day']}', '{$_GET['hour']}', '{$_GET['minute']}', '{$_GET['second']}')";
		if($connection->query($sql)){
			echo "Successful Log";
			mail('9702082235@messaging.sprintpcs.com', '', 'A detection has been made');
		}else{
			echo "Failure to Log";
		}
	}
}
?>