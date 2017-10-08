<!DOCTYPE html>
<html>
<head>
	<style>
	table {
		font-family: arial, sans-serif;
		border-collapse: collapse;
		width: 100%;
	}

	td, th {
		border: 1px solid #dddddd;
		text-align: left;
		padding: 8px;
	}

	tr:nth-child(even) {
		background-color: #dddddd;
	}
</style>
</head>
<body>
	<h1>Listado de Ficheros</h1>
	<table>
		<tr>
			<th>Fichero</th>
			<th>Tamaño</th>
		</tr>
		<?php
		if ($handle = opendir('.')) {
			while (false !== ($entry = readdir($handle))) {
				if ($entry != "." && $entry != ".." && $entry != "index.php" && $entry != ".htaccess") {
					echo "<tr>";
					echo "<td><a href=\"".$entry."\">".$entry."</td>";	
					echo "<td>".round(filesize($entry)/1000000)." MB</td>";
					echo "</tr>";
				}
			}
			closedir($handle);
		}
		?>
	</table>
</body>
</html>