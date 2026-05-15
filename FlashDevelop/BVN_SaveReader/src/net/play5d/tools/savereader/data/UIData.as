package net.play5d.tools.savereader.data {
	
	import fl.controls.Button;
	import fl.controls.Label;
	import fl.controls.ComboBox;
	import fl.controls.TextInput;
	import fl.data.DataProvider;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.IOErrorEvent;
	import flash.net.FileReference;
	import net.play5d.tools.savereader.Main;
	import net.play5d.tools.savereader.utils.ObjectUtils;
	import net.play5d.tools.savereader.utils.UIUtils;
	import net.play5d.tools.savereader.utils.Loger;
	
	/**
	 * ...
	 * @author tester
	 */
	public class UIData {
		
		private static const STATUS:Object = {
			_normal: 0,
			_continue: 1,
			_break: 2
		};
		private static const NORMAL:int = STATUS._normal;
		private static const CONTINUE:int = STATUS._continue;
		private static const BREAK:int = STATUS._break;
		
		private static var _main:Main;
		
		public function UIData():void {}
		
		public static function init(main:Main):void {
			_main = main;
		}
		
		/**
		 * 获取 ui 组件列表及其附带参数
		 * 
		 * @return	uiList
		 */
		public static function getUIList():Array {
//			trace(NORMAL, CONTINUE, BREAK);
			/**
			 * 遍历已有 fighter 数据。
			 */
			function forEachFighter(func:Function = null):void {
				for (var i:int = 0; i < _main.mosouObj.mosou.fighterData.length; i++) {
					var fighterObj:Object = _main.mosouObj.mosou.fighterData[i];
					
					if (func != null) {
						var status:int = func(fighterObj);
						if (status == CONTINUE) {
							continue;
						}
						if (status == BREAK) {
							break;
						}
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////
			
			var dataProvider:DataProvider = new DataProvider();
			forEachFighter(function (fighterObj:Object):int {
				var addObj:Object = {label: fighterObj.id};
				dataProvider.addItem(addObj);
				
				return NORMAL;
			});
			
			
			function getLevel():int {
				var level:int;
				
				var cb:ComboBox = UIUtils.getUIByName("cb_holdFighter") as ComboBox;
				forEachFighter(function (fighterObj:Object):int {
					//var currentFighter:Object = cb.selectedItem;
					trace(cb == null)
					if (fighterObj.id == "") {
						level = fighterObj.level;
						
						return BREAK;
					}
					
					return NORMAL;
				});
				
				return level;
			}
			
			function getExp():int {
				var exp:int;
				
				return exp;
			}
			
			/* 组件间隔 22 像素 */
			var uiList:Array = [{
				type: Button,
				x: 10,
				y: 10,
				w: 280,
				param: {
					label: "保存存档文件"
				},
				funcArray: [{
					type: MouseEvent.CLICK,
					func: function (e:Event):void {
						var file:FileReference = new FileReference();
						var ti:TextInput = UIUtils.getUIByName("ti_money") as TextInput;
						
						_main.mosouObj.mosou.money = int(ti.text);
						var data:String = ObjectUtils.obj2String(_main.mosouObj);
//						Loger.log(data);
						function onComplete(e:Event):void {
							file.removeEventListener(Event.COMPLETE, onComplete);
							
							Loger.log("保存成功！");
						}
						function onIOError(e:IOErrorEvent):void {
							file.removeEventListener(IOErrorEvent.IO_ERROR, onIOError);
							
							Loger.log("保存失败！");
						}
						file.addEventListener(Event.COMPLETE, onComplete);
						file.addEventListener(IOErrorEvent.IO_ERROR, onIOError);
						file.save(data, _main.SAVE_PATH);
					}
				}]
			}, {
				type: Label,
				x: 10,
				y: 42,
				w: 135,
				param: {
					text: "金钱"
				}
			}, {
				type: TextInput,
				x: 150,
				y: 42,
				w: 135,
				param: {
					name: "ti_money",
					text: String(_main.mosouObj.mosou.money)
				}
			}, {
				type: Label,
				x: 10,
				y: 100,
				w: 135,
				param: {
					text: "已有角色数据修改"
				}
			}, {
				type: ComboBox,
				x: 150,
				y: 100,
				w: 135,
				param: {
					name: "cb_holdFighter",
					dataProvider: dataProvider
				}
			}, {
				type: Label,
				x: 10,
				y: 132,
				w: 75,
				param: {
					name: "",
					text: "当前等级：" + getLevel()
				}
			}, {
				type: Label,
				x: 150,
				y: 132,
				w: 65,
				param: {
					name: "",
					text: "当前经验："
				}
			}];
			
			return uiList;
		}
		
		public static function updateListData():void {
			
		}
	}
}