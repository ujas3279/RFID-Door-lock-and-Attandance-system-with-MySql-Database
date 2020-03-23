<?php
require_once 'connect.php';
$sql="update data set attandance=0 where attandance=1";
mysqli_query($connect,$sql);
header("location:present_list.php");
?>