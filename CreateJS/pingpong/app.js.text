var stage = new createjs.Stage("demoCanvas");
var keys = {};
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
stage.addChild(circle);

var bar = new createjs.Shape();
bar.width = 50;
bar.height = 10;
bar.x = (canvas.width - bar.width) / 2;
bar.y = 0;
bar.updatePosition = function() {
	if (keys[37] && bar.x > 0) {
		bar.x -= 1;
	}
    if (keys[39] && bar.x < canvas.width - bar.width) {
    	bar.x += 1;
    }
}
bar.graphics.beginFill("black").drawRect(0, 0, bar.width, bar.height);
stage.addChild(bar);

var vector = {
	a: 1,
	b: 1
};

var tick = function() {
	bar.updatePosition();
  	circle.updatePosition(bar);
  	stage.update();
}

createjs.Ticker.addEventListener("tick", tick);
createjs.Ticker.setFPS(120);
var endGame = function() {
	createjs.Ticker.removeEventListener("tick", tick);
	alert("You lose!!");
}
document.onkeydown = function(event) {
    keys[event.keyCode] = true;
};
document.onkeyup =function(event) {
    keys[event.keyCode] = false;
};
