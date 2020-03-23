<?php require_once 'connect.php';?>
<!DOCTYPE html>
<html>
<head>
	<title>	</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
</head>
<body>
<div class="container">
   <h1>Present List</h1></br>
  <div class="table-responsive">
	<table  class='table'>
        <thead>
     	<tr>
     		<th>Student Name</th>
     	</tr>
        </thead>
        <tbody>
     	<tr>
     	</tr>
   <?php
        $sql="select Student_name from data where attandance=1";
        $result=$connect->query($sql);
        
		while($data=$result->fetch_assoc())
	  {
		  
          echo "<tr><td>".$data[@Student_name]."</td></tr>";
	  }
	  
   ?>
</tbody>

</table>
</div>
   <h1>Absent List</h1>
<div class="table-responsive">
   <table class="table">
       <thead>
     	<tr>
     		<th>Student Name</th>
     	</tr>
       </thead>
        <tbody>       
   <?php
        $sql="select Student_name from data where attandance=0";
	    $result=$connect->query($sql);

	    while($data=$result->fetch_assoc())
	  {
          echo "<tr><td>".$data[@Student_name]."</td></tr>";
	  }
   ?>
 </tbody>
</table>
</div>
<button type="button" onclick="location.href = 'generate_csv.php';" class="btn btn-success" onclick="">GENERATE CSV</button>
<button type="button" onclick="location.href = 'reset.php';" class="btn btn-danger">RESET ATTANDANCE</button>
</div>
</body>
</html>