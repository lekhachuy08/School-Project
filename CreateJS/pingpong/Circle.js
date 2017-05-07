var canvas = document.getElementById('demoCanvas');

var circle = new createjs.Shape();
circle.x = canvas.width / 2;
circle.y = canvas.height / 2;
circle.radius = 20;
circle.touch = function(bar) {
	return ((circle.y <= circle.radius + bar.height) && (bar.x <= circle.x && circle.x < bar.x + bar.width))
}
circle.updatePosition = function(bar) {
	circle.x += vector.a;
	circle.y += vector.b;
	if (circle.x === canvas.width - circle.radius || circle.x === circle.radius) {
		vector.a = -vector.a;
	}
	if (circle.y === canvas.height - circle.radius || circle.touch(bar)) {
		vector.b = -vector.b;
	}
	if (circle.y === circle.radius) {
		endGame();
	}
}
circle.graphics.beginFill("DeepSkyBlue").drawCircle(0, 0, circle.radius);

export(circle);