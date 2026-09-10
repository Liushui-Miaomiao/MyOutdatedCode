Public NotInheritable Class Config

	Public Shared XMLData As Xml.XmlDocument
	Public Shared bIsChinese As Boolean
	Public Shared oldVersionData As ArrayList
	Public Shared newVersionData As ArrayList

	Public Shared binDir As String
	Public Shared configDir As String
	Public Shared dataDir As String
	Public Shared runtimeDir As String
	Public Shared toolDir As String

	''' <summary>
	''' 检查路径数组
	''' </summary>
	Public Shared checkUrlArray() As String = {"", "", "", "", ""}

	''' <summary>
	''' 载入 config.xml 文件
	''' </summary>
	''' <returns>载入文件是否成功</returns>
	Public Shared Function Load() As Boolean
		XMLData = New Xml.XmlDocument

		''''''''''''''''''''载入配置文件''''''''''''''''''''
		Try
			XMLData.Load("config/config.xml")
		Catch ex As Exception
			Return False
		End Try
		''''''''''''''''''''''''''''''''''''''''''''''''''''

		Return True
	End Function

	''' <summary>
	''' 通过节点名称获取对应值
	''' </summary>
	''' <param name="sName">节点名称</param>
	''' <returns>节点名称对应值</returns>
	Public Shared Function GetValueByName(ByVal sName As String) As String
		Dim value As String
		Dim xmlNode As Xml.XmlNode

		''''''''''''''''''''取标签XML节点''''''''''''''''''''
		Try
			xmlNode = XMLData.SelectSingleNode("//label//" + sName)
		Catch ex As Exception
			MsgBox(GetValueByName("label") + "lable." + sName, MsgBoxStyle.Critical, GetValueByName("label_title"))

			Return vbNullString
		End Try
		'''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''是中文系统返回中文，否则返回英文''''''''''''''''''''
		If bIsChinese Then
			value = xmlNode.Attributes(0).InnerText
		Else
			value = xmlNode.Attributes(1).InnerText
		End If
		''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		Return value
	End Function

	''' <summary>
	''' 检测文件完整
	''' </summary>
	''' <returns>所需文件是否完整</returns>
	Public Shared Function CheckFile() As Boolean
		Dim checkUrlXmlNodeList As Xml.XmlNodeList

		''''''''''''''''''''取检查路径XML节点''''''''''''''''''''
		Try
			checkUrlXmlNodeList = XMLData.SelectSingleNode("//data//check_url").ChildNodes
		Catch ex As Exception
			MsgBox(GetValueByName("label") + "data.check_url", MsgBoxStyle.Critical, GetValueByName("label_title"))

			Return False
		End Try
		'''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		Dim bIsSuccess As Boolean = True

		''''''''''''''''''''遍历节点检查文件''''''''''''''''''''
		For i As Integer = 0 To checkUrlXmlNodeList.Count - 1
			Dim checkUrlXmlNode As Xml.XmlNode = checkUrlXmlNodeList(i)
			Dim index As Integer = Integer.Parse(checkUrlXmlNode.Attributes(0).InnerText)
			Dim checkUrl As String = GetDirectoryByIndex(index) + checkUrlXmlNode.Attributes(1).InnerText

			If Dir(checkUrl) = "" Then
				MsgBox(GetValueByName("notfind") + checkUrl, MsgBoxStyle.Critical, GetValueByName("notfind_title"))

				bIsSuccess = False
			Else
				checkUrlArray(i) = checkUrl
			End If
		Next
		''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		Return bIsSuccess
	End Function

	''' <summary>
	''' 通过索引得到目录
	''' </summary>
	''' <param name="iIndex">索引</param>
	''' <returns>对应目录</returns>
	Public Shared Function GetDirectoryByIndex(ByVal iIndex As Integer) As String
		Dim directoryName As String
		Dim directoryUrlXmlNodeList As Xml.XmlNodeList

		''''''''''''''''''''取目录XML节点''''''''''''''''''''
		Try
			directoryUrlXmlNodeList = XMLData.SelectSingleNode("//data//directory").ChildNodes
		Catch ex As Exception
			MsgBox(GetValueByName("label") + "data.directory", MsgBoxStyle.Critical, GetValueByName("label_title"))

			Return vbNullString
		End Try
		'''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''通过索引取目录名称''''''''''''''''''''
		Try
			directoryName = directoryUrlXmlNodeList(iIndex).Attributes(0).InnerText
		Catch ex As Exception
			MsgBox(GetValueByName("overflow") + CStr(iIndex), MsgBoxStyle.Critical, GetValueByName("overflow_title"))

			Return vbNullString
		End Try
		''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		Return directoryName
	End Function
End Class
