package sound {
	
	import flash.media.Sound;
	import flash.utils.ByteArray;
	
	public class SoundByteArray extends Sound{
		
		public function SoundByteArray(bytes:ByteArray = null) {
			super(null, null);
			
			if (bytes) {
				loadBytes(bytes);
			}
		}
		
		public function loadBytes(value:ByteArray):void {
			value.position = 0;
			
			while (value.bytesAvailable > 0) {
				var bytes:ByteArray = new ByteArray();
				var len:uint = Math.min(value.bytesAvailable, 40 * 1024);
				
				value.readBytes(bytes, 0, len);
				
				this.loadCompressedDataFromByteArray(bytes, bytes.bytesAvailable);
			}
			
			value.clear();
		}
	}
}