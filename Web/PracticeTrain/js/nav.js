/* 动态创建 div */
// 小米名称数组
var xmNameList = ["小米MIX FOLD", "小米11 Ultra", "小米11 Pro", "小米11 青春版", "小米10S", "小米11"];
// 小米价格数组
var xmRmbList = ["9999", "5999", "4999", "2299", "3299", "3999"];

// 红米名称数组
var hmNameList = ["Note 10 Pro", "Note 10 5G", "K40 游戏增强版", "K40 Pro 系列", "Redmi K40", "Redmi Note 9 系列"];
// 红米价格数组
var hmRmbList = ["1499", "999", "1999", "2799", "1999", "999"];

getData();
function getData() {
	for (var i = 0; i < 6; i++) {
		var goodsDiv = $("<div class=\"goodsDiv\"></div>");
		// var goodsDiv = document.createElement("div");
		$(".downCon").append(goodsDiv);

		// 动态创建图片标签
		var goodsImg = $("<img />");
		goodsDiv.append(goodsImg);

		// 动态创建 <p></p> 标签
		var goodsName = $("<p class=\"goodsName\"></p>");
		goodsDiv.append(goodsName);

		var goodsRmb = $("<p class=\"goodsRmb\"></p>");
		goodsDiv.append(goodsRmb);
	}
}

$(".logoUl li").mouseenter(function() {
	var nameList;
	var rmbList;
	switch ($(this).index()) {
		case 0:
			nameList = xmNameList;
			rmbList = xmRmbList;
			for (var i = 0; i < 6; i++) {
				var box = $(".goodsDiv").eq(i);
				box.children(1).attr("src", "image/xm/" + (i + 1) + ".png");
				box.children(".goodsName").text(nameList[i]);
				box.children(".goodsRmb").text(rmbList[i] + " 元起");
			}
			break;
		case 1:
			nameList = hmNameList;
			rmbList = hmRmbList;
			for (var i = 0; i < 6; i++) {
				var box = $(".goodsDiv").eq(i);
				box.children(1).attr("src", "image/hm/" + (i + 1) + ".png");
				box.children(".goodsName").text(nameList[i]);
				box.children(".goodsRmb").text(rmbList[i] + " 元起");
			}
			break;
		default:

	}
});