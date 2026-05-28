layui.define(["layer", "util"], function (exports) {
	var layer, util;
	layer	= layui.layer;
	util	= layui.util;

	// 屏幕右下固定条
	util.fixbar({
		css: {
			right	: 50,
			bottom	: 100
		},
		bgcolor: "#393D49",
		click: function (type) {
			// TO DO
		}
	});

	exports("global", {});
});