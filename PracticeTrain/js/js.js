$(".topCar").mouseenter(function() {
	$(".carList").stop().slideDown(200);
	$(".topCar").css("background", "#FFFFFF");
	$(".topCar span").css("color", "#FF6700");
	$(".topCar img").attr("src", "image/car2.png");
}).mouseleave(function() {
	$(".carList").stop().slideUp(500);
	setTimeout(function() {
		$(".topCar").css("background", "#424242");
		$(".topCar span").css("color", "#b0b0b0");
		$(".topCar img").attr("src", "image/car1.png");
	}, 500);
});

// 鼠标穿过导航栏
$(".logoUl li").mouseenter(function() {
	if ($(this).index() < 7) {
		$(".downList").stop().slideDown(200);
	}
}).mouseleave(function() {
	$(".downList").stop().slideUp(200);
});

// 鼠标放到下拉菜单上，菜单要停留住
$(".downList").mouseenter(function() {
	$(".downList").stop().slideDown(0);
}).mouseleave(function() {
	$(".downList").stop().slideUp(200);
});