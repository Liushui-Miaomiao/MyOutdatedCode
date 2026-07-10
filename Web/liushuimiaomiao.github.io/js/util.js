/* 工具类 */

/**
 * 前往 404 页面
 */
function goto404() {
    window.location.href = "404.html";
}

/**
 * 写页眉公用信息
 * @param {string} title 标题
 */
function header(title) {
    document.writeln("<meta charset='utf-8'/>");
    document.writeln("<link rel='icon' href='fav.ico'/>");
    document.writeln("<link href='css/glo.css' type='text/css' rel='stylesheet'/>");
    document.writeln("<title>" + title +"</title>");
    
    addOnload(function() {
        var h1 = document.createElement("h1");
        h1.innerText = title;
        
        var body = document.body;
        body.insertBefore(h1, body.firstElementChild)
    });
}

/**
 * 写页脚备案信息
 */
function footer() {
    document.writeln("<p>京ICP备2020036654号-9</p>");
}

/**
 * 创建表头
 * @param {HTMLElement} div  表格标签div
 * @param {string[]}    head 表格头数组
 */
function createTableHead(div, head) {
    var table = document.createElement("table");
    table.id = "table";
    var tr = document.createElement("tr");
    
    for (var i = 0; i < head.length; i++) {
        var td = document.createElement("td");
        td.innerHTML = "<b>" + head[i] + "</b>";
        tr.appendChild(td);
    }
    
    table.appendChild(tr);
    div.appendChild(table);
}

/**
 * 获取参数
 * @param  {string} name 参数名称
 * @return {string}      参数值
 */
function getParameter(name) {
    var query = window.location.search.substring(1);
    var vars = query.split("&");
    
    var value = null;
    for (var i = 0; i < vars.length; i++) {
        var pair = vars[i].split("=");
        
        if (pair[0] === name) {
            value = pair[1];
            break;
        }
    }
    
    return value;
}

/**
 * 添加 onload 事件函数
 * @param {Function} onLoadFunc 事件函数
 */
function addOnload(onLoadFunc) {
    // 把现有的 onload 事件存入 lastOnload
    var lastOnload = window.onload;
    
    // 如果还没有绑定任何函数，就把事件函数赋值给它
    if (typeof window.onload !== "function") {
        window.onload = onLoadFunc;
        return;
    }
    
    // 如果绑定了函数，那么追加到末尾
    window.onload = function() {
        lastOnload();
        onLoadFunc();
    }
}

/**
 * 添加数据
 * @param {Object} data 数据
 */
function addData(data) {
    var table = document.getElementById("table");
    
    for (var i = 0; i < data.length; i++) {
        var itm = data[i];
        var tr = _addTr(itm);
        
        table.appendChild(tr);
    }
}

/**
 * 添加一个 tr 标签
 * @param  {Object} itm          节点
 * @return {HTMLTableRowElement} tr标签
 */
function _addTr(itm) {
    var tr = document.createElement("tr");
    
    for (var key in itm) {
        // DW要求使用属性前必须判断是否具有相关属性
        if (!itm.hasOwnProperty(key)) {
            continue;
        }
        
        var td = _addTd(key, itm[key]);
        tr.appendChild(td);
    }
    
    return tr;
}

/**
 * 添加一个 td 标签
 * @param  {string} key           键
 * @param  {string} value         值
 * @return {HTMLTableCellElement} td标签
 */
function _addTd(key, value) {
    var td = document.createElement("td");
    
    switch (key) {
    case "download":
        var a = document.createElement("a");
        a.href = value;
        a.innerHTML = "下载";
        
        td.appendChild(a);
        break;
    case "img":
        if (value !== "") {
            var img = document.createElement("img");
            img.src = "img/" + value;
            img.title = value;
            
            td.appendChild(img);
            break;
        }
        
        value = "暂无图片";
    default :
        // img和默认情况的内容
        td.innerHTML = value;
    }
    
    return td;
}