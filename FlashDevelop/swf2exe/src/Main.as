/**
 * Copyright (C) 2021, 5DPLAY Game Studio
 * All rights reserved.
 * 
 * This software is distributed under the MIT license.
 * Any person or organization may use this library free of charge, 
 * but it must follow the following points :
 * 
 * 1. No person or organization may claim to 
 *    have written the original source code.
 * 
 * 2. In any case, the author is not liable for 
 *    any consequences caused by the use of part 
 *    of the code of this software.
 * 
 * 3. This section shall not be deleted or altered 
 *    from any source.
 * 
 */

package {
	
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.net.FileFilter;
	import flash.net.URLLoader;
	import flash.net.URLLoaderDataFormat;
	import flash.net.URLRequest;
	import flash.text.TextField;
	import flash.utils.ByteArray;
	
	import net.play5d.kyo.display.ui.KyoSimpButton;
	import net.play5d.tools.swf2exe.utils.Log;
	import net.play5d.tools.swf2exe.utils.ResUtils;
	
	/**
	 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
	 * @version	1.0
	 * @since	4/27/2021 4:59 PM
	 */
	[SWF(frameRate = "30", backgroundColor = "#ffffff", width = "800", height = "600")]
	public class Main extends Sprite {
		
		private var _sp					:Sprite;
		private var _txt				:TextField;
		
		private var _btns				:Array;
		
		private var _flashPlayerPath	:String;
		private var _swfPath			:String;
		private var _exePath			:String;
		
		private var _flashPlayerData	:ByteArray;
		private var _swfData			:ByteArray;
		
		private var _flashPlayerClass	:Class;
		
		/**
		 * Constructor.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:26 PM
		 * 
		 * @return	void
		 */
		public function Main():void {
			if (stage) {
				initlize();
			}
			else {
				addEventListener(Event.ADDED_TO_STAGE, initlize);
			}
		}
		
		/**
		 * Initlize.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:05 PM
		 * 
		 * @param	e	Event, <b>required</b>.
		 * 
		 * @return	void
		 */
		private function initlize(e:Event = null):void {
			removeEventListener(Event.ADDED_TO_STAGE, initlize);
			
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.align 	= StageAlign.TOP_LEFT;
			stage.addEventListener(Event.RESIZE, resizeHandler);
			
			_sp 	= new Sprite();
			_txt 	= new TextField();
			_btns 	= new Array();
			
			addButton("Select FP");
			addButton("Select SWF");
			addButton("Go!");
			
			Log.init(_txt);
			
			_sp.addChild(_txt);
			addChild(_sp);
			
			Log.log("Welcome to use SWF files to convert to EXE files!");
			
			_flashPlayerClass = ResUtils.I.getDefaultPlayerClass();
			if (_flashPlayerClass != null) {
				_flashPlayerData = new _flashPlayerClass() as ByteArray;
			}
			if (_flashPlayerData != null) {
				Log.log("Built-in player initialized successfully!");
			}
			
			
			resizeHandler(null);
		}
		
		/**
		 * Listen for window change events.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:05 PM
		 * 
		 * @param	e	Event, <b>required</b>.
		 * 
		 * @return	void
		 */
		private function resizeHandler(e:Event):void {
			var w:Number = stage.nativeWindow.width;
			var h:Number = stage.nativeWindow.height;
			
			_sp.graphics.clear();
			_sp.graphics.beginFill(0xFFFFFF, 1);
			_sp.graphics.drawRect(0, 0, w, h);
			_sp.graphics.endFill();
			
			_txt.width 	= w;
			_txt.height = h - 80;
			
			for(var i:int = 0; i < _btns.length; i++) {
				_btns[i].x = 10 + i * 120;
				_btns[i].y = h - 80;
			}
		}
		
		/**
		 * Add button.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0
		 * @since	4/27/2021 5:11 PM
		 * 
		 * @param	label	Button label, <b>required</b>.
		 * 
		 * @return	void
		 */
		private function addButton(label:String):void {
			var btn:KyoSimpButton = new KyoSimpButton(label, 100, 30);
			
			btn.name = label;
			_btns.push(btn);
			
			_sp.addChild(btn);
			
			btn.addEventListener(MouseEvent.CLICK, btnHandler);
		}
		
		/**
		 * Listens for button events
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0.
		 * @since	4/27/2021 5:11 PM
		 * 
		 * @param	e	Event, <b>required</b>.
		 * 
		 * @return	void
		 */
		private function btnHandler(e:MouseEvent):void {
			var file		:File 		= new File();
			var fileFilter	:FileFilter = null;
			var btnName		:String 	= (e.currentTarget as KyoSimpButton).name;
			
			switch (btnName) {
				case "Select FP" :
					fileFilter = new FileFilter("Flash Player", "*.exe");
					
					file.addEventListener(Event.SELECT, function(e:Event):void {
						var target:File = e.target as File;
						if (target == null) {
							Log.log("The target is empty!");
							return;
						}
						_flashPlayerPath = target.nativePath;
						
						Log.log("The following path file will be used as the player : " + _flashPlayerPath);
						loadFlashPlayer();
					});
					
					file.browseForOpen("Select Flash Player", [fileFilter]);
					break;
				case "Select SWF" :
					fileFilter = new FileFilter("SWF files", "*.swf");
					
					file.addEventListener(Event.SELECT, function(e:Event):void {
						var target:File = e.target as File;
						if (target == null) {
							Log.log("The target is empty!");
							return;
						}
						_swfPath = target.nativePath;
						_exePath = _swfPath.slice(0, _swfPath.lastIndexOf(".")) + ".exe";
						
						Log.log("SWF \t\t: " + _swfPath);
						Log.log("Output \t: " + _exePath);
						
						loadSwf();
					});
					
					file.browseForOpen("Select SWF file", [fileFilter]);
					break;
				case "Go!" :
					connectionData();
					break;
			}
			
			file 		= null;
			fileFilter 	= null;
		}
		
		/**
		 * Load Flash Player
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0.
		 * @since	4/27/2021 5:20 PM
		 * 
		 * @return	void
		 */
		private function loadFlashPlayer():void {
			Log.log("Loading Flash Player...");
			
			var flashPlayerLoader:URLLoader = new URLLoader(new URLRequest(_flashPlayerPath));
			
			flashPlayerLoader.dataFormat = URLLoaderDataFormat.BINARY;
			flashPlayerLoader.addEventListener(Event.COMPLETE, loadFlashPlayerComplete);
			
			function loadFlashPlayerComplete(e:Event):void {
				flashPlayerLoader.removeEventListener(Event.COMPLETE, loadFlashPlayerComplete);
				
				_flashPlayerData = (flashPlayerLoader.data) as ByteArray;
				
				Log.log("The new Flash Player is ready!");
			}
		}
		
		/**
		 * Load SWF file.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0.
		 * @since	4/27/2021 5:20 PM
		 * 
		 * @return	void
		 */
		private function loadSwf():void {
			Log.log("Loading SWF file...");
			
			var swfLoader:URLLoader = new URLLoader(new URLRequest(_swfPath));
			swfLoader.dataFormat 	= URLLoaderDataFormat.BINARY;
			swfLoader.addEventListener(Event.COMPLETE, loadSwfComplete);
			
			function loadSwfComplete(e:Event):void {
				swfLoader.removeEventListener(Event.COMPLETE, loadSwfComplete);
				
				_swfData = (swfLoader.data) as ByteArray;
				
				Log.log("The SWF is ready!");
			}
		}
		
		/**
		 * Linked file data.
		 * 
		 * @author	Liushui_Miaomiao,	liushui_miaomiao@163.com
		 * @version	1.0.
		 * @since	4/27/2021 5:20 PM
		 * 
		 * @return	void
		 */
		private function connectionData():void {
			if (!_flashPlayerData || !_swfData){
				Log.log("Flash Player or SWF data is not loaded!");
				
				return;
			}
			Log.log("Linked file data...");
			
			// Start Link.
			var outExeData:ByteArray = new ByteArray();
			outExeData.writeBytes(_flashPlayerData);
			outExeData.writeBytes(_swfData);
			
			// Linking.
			outExeData[outExeData.length] = 0x56;
			outExeData[outExeData.length] = 0x34;
			outExeData[outExeData.length] = 0x12;
			outExeData[outExeData.length] = 0xFA;
			outExeData[outExeData.length] = _swfData.length;
			outExeData[outExeData.length] = _swfData.length >> 0x08;
			outExeData[outExeData.length] = _swfData.length >> 0x10;
			outExeData[outExeData.length] = _swfData.length >> 0x18;
			
			Log.log("Data connection over! Start saving the file...");
			
			// Save new file.
			var file:File 		= new File(_exePath);
			var fs	:FileStream = new FileStream();
			
			fs.open(file, FileMode.WRITE);
			fs.writeBytes(outExeData);
			
			fs.close();
			
			Log.log("Conversion success!");
		}
	}
}