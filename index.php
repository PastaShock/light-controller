<head>
	<link rel=stylesheet type="text/css" href="style.css">
</head>
<body>
	<h1>Light controller</h1>
	<div class='title area'>
		<p>Toggle the lights on and off:</p>
	</div>
	<div class='switch panel' onclick='Switch()'>
		<form action="action.php" method="POST">
			<label>
				lights: 
				<input type="range" id="lightswitch" name="lightswitch" min="0" max="1" />
			</label>
		</form>
	</div>
	<button class="submit" id="phpButton">Submit</button>
	<script>
		var switch = document.getElementById('lightswitch');
		function Switch() {
			if (switch.value == 1) {
					switch.value = 0;
				} else {
					switch.value = 1;
			}
			switch.style.display = 'none';
			switch.style.display = 'block';
		}
	</script>
</body>
