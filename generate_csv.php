<?php 
require_once 'connect.php';
$sql="select * from data where attandance=1";
		$result=$connect->query($sql);
		$delimiter = ",";
        $filename = "Attandance". ".csv";
        $f = fopen('php://memory', 'w');
        $fields = array('ID', 'UID', 'Student Name', 'Status');
        fputcsv($f, $fields, $delimiter);
		while($data=$result->fetch_assoc())
	  {
		  fputcsv($f, $data);
      }
      fseek($f, 0);
	  header('Content-Type: text/csv');
      	  header('Content-Disposition: attachment; filename="' . $filename . '";');
	  fpassthru($f);
	  exit;
?>
