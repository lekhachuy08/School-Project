var canvas = document.getElementById('demoCanvas');

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

export(bar);