package net.play5d.tools.savereader.utils {
	
	/**
	 * ...
	 * @author tester
	 */
	
	public class ObjectUtils {
		
		/**
		 * 构造函数
		 */
		public function ObjectUtils():void {}
		
		/**
		 * 是否具有某个属性。
		 * 
		 * @param	key		key
		 * @return	Boolean
		 */
		public static function hasProperty(obj:Object, key:String):Boolean {
			for (var k:String in obj) {
				if (k == key) {
					return true;
				}
			}
			
			return false;
		}
		
		/**
		 * 添加属性
		 * 
		 * @param	key
		 * @param	value
		 */
		public static function addProperty(obj:Object, key:String, value:Object):void {
			obj[key] = value;
		}
		
		/**
		 * 删除属性
		 * 
		 * @param	key
		 */
		public static function removeProperty(obj:Object, key:String):void {
			if (!hasProperty(obj, key)) {
				return;
			}
			
			var newObject:Object = {};
			for (var k:String in obj) {
				if (k == key) {
					continue;
				}
				
				newObject[k] = obj[k];
			}
			
//			trace(JSON.stringify(_object));
//			trace(JSON.stringify(newObject));
			obj = newObject;
		}
		
		/**
		 * 转换为字符串
		 * 
		 * @param	obj
		 * @return
		 */
		public static function obj2String(obj:Object):String {
			return JSON.stringify(obj);
		}
	}

}