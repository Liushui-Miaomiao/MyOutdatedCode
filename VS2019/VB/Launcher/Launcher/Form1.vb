Imports System.Reflection

Public Class Form1

	''''''''''''''''''''引用库函数''''''''''''''''''''
	Private Declare Function GetSystemDefaultLCID Lib "Kernel32" () As Short
	''''''''''''''''''''''''''''''''''''''''''''''''''

	''''''''''''''''''''类属性''''''''''''''''''''
	Private bIsRunOFTools As Boolean = False
	''''''''''''''''''''''''''''''''''''''''''''''

	''' <summary>
	''' 启动窗口后执行的子程序
	''' </summary>
	''' <param name="sender">发送器</param>
	''' <param name="e">事件参数</param>
	Private Sub LaunchForm_Load(sender As Object, e As EventArgs) Handles MyBase.Load
		''''''''''''''''''''判断操作系统是否为中文''''''''''''''''''''
		Config.bIsChinese = GetSystemDefaultLCID() = 2052
		'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''加载配置文件''''''''''''''''''''
		If Not Config.Load() Then
			MsgBox("The config file could not be found!", MsgBoxStyle.Critical, "Error")

			End
		End If
		''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''初始化路径''''''''''''''''''''
		Config.binDir = Config.GetDirectoryByIndex(0)
		Config.configDir = Config.GetDirectoryByIndex(1)
		Config.dataDir = Config.GetDirectoryByIndex(2)
		Config.runtimeDir = Config.GetDirectoryByIndex(3)
		Config.toolDir = Config.GetDirectoryByIndex(4)
		''''''''''''''''''''''''''''''''''''''''''''''''''

		'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''检查文件''''''''''''''''''''
		If Not Config.CheckFile() Then
			End
		End If
		''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''置列表框数据''''''''''''''''''''
		SetOldListBoxData()
		SetNewListBoxData()
		''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''置窗口文字信息''''''''''''''''''''
		Text = Config.GetValueByName("title")
		SelectLable.Text = Config.GetValueByName("select")
		LaunchButton.Text = Config.GetValueByName("launch")
		OldRadioButton.Text = Config.GetValueByName("old")
		NewRadioButton.Text = Config.GetValueByName("new")

		OldListBox.DataSource = Config.oldVersionData
		NewListBox.DataSource = Config.newVersionData

		OldListBox.ClearSelected()
		NewListBox.ClearSelected()
		'''''''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''置默认启动项为最新版''''''''''''''''''''
		NewListBox.SelectedItem = CStr(Config.newVersionData.Item(Config.newVersionData.Count - 1))
		''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

		Try
			Icon = Icon.ExtractAssociatedIcon(Assembly.GetExecutingAssembly().Location)
		Catch ex As ArgumentException

		End Try
	End Sub

	''' <summary>
	''' 置旧版游戏列表框数据
	''' </summary>
	Private Sub SetOldListBoxData()
		Dim oldVersionXmlNodeList As Xml.XmlNodeList

		Try
			oldVersionXmlNodeList = Config.XMLData.SelectSingleNode("//data//version//old").ChildNodes
		Catch ex As Exception
			MsgBox(Config.GetValueByName("label") + "data.version.old", MsgBoxStyle.Critical, Config.GetValueByName("label_title"))

			Return
		End Try

		Config.oldVersionData = New ArrayList
		For i As Integer = 0 To oldVersionXmlNodeList.Count - 1
			Config.oldVersionData.Add(oldVersionXmlNodeList(i).Attributes(0).InnerText)
		Next
	End Sub

	''' <summary>
	''' 置新版列表框数据
	''' </summary>
	Private Sub SetNewListBoxData()
		Dim newVersionXmlNodeList As Xml.XmlNodeList

		Try
			newVersionXmlNodeList = Config.XMLData.SelectSingleNode("//data//version//new").ChildNodes
		Catch ex As Exception
			MsgBox(Config.GetValueByName("label") + "data.version.new", MsgBoxStyle.Critical, Config.GetValueByName("label_title"))

			Return
		End Try

		Config.newVersionData = New ArrayList
		For i As Integer = 0 To newVersionXmlNodeList.Count - 1
			Config.newVersionData.Add(newVersionXmlNodeList(i).Attributes(0).InnerText)
		Next
	End Sub

	''' <summary>
	''' 按钮_启动游戏 被单击
	''' </summary>
	''' <param name="sender">发送器</param>
	''' <param name="e">事件参数</param>
	Private Sub LaunchButton_Click(sender As Object, e As EventArgs) Handles LaunchButton.Click
		'运行游戏所需的命令行
		Dim commandLine As String

		Dim batUrl As String = """" + Config.checkUrlArray(1) + """"
		Dim adlUrl As String = """" + Config.checkUrlArray(0) + """"
		Dim runTimeUrl As String = """" + Config.GetDirectoryByIndex(3).Replace("\", "") + """"
		Dim metaDataUrl As String
		Dim rootDirectoryUrl As String

		If NewRadioButton.Checked Then
			'运行新版本

			''''''''''''''''''''判断是否为空''''''''''''''''''''
			If CStr(NewListBox.SelectedItem) = "" Then
				MsgBox(Config.GetValueByName("notselect"), MsgBoxStyle.Exclamation, Config.GetValueByName("notselect_title"))

				Return
			End If
			''''''''''''''''''''''''''''''''''''''''''''''''''''

			''''''''''''''''''''自动运行离线修复工具''''''''''''''''''''
			If Not bIsRunOFTools Then
				Try
					Shell("""" + Config.checkUrlArray(3) + """", AppWinStyle.Hide, True)
				Catch ex As Exception
					MsgBox(Config.GetValueByName("execute"), MsgBoxStyle.Critical, Config.GetValueByName("execute_title"))

					Return
				End Try

				bIsRunOFTools = True
			End If
			''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

			metaDataUrl = """" + Config.GetDirectoryByIndex(1) + "application\" + CStr(NewListBox.SelectedItem) + ".xml"""

			''''''''''''''''''''特例处理''''''''''''''''''''
			Dim version = CStr(NewListBox.SelectedItem)
			If version = "3.4" Or version = "3.5" Or version = "3.6" Then
				rootDirectoryUrl = """" + Config.GetDirectoryByIndex(2) + "new\" + version + """"
			Else
				rootDirectoryUrl = """" + Config.GetDirectoryByIndex(2) + "new"""
			End If
			''''''''''''''''''''''''''''''''''''''''''''''''
		Else
			'运行旧版本

			''''''''''''''''''''判断是否为空''''''''''''''''''''
			If CStr(OldListBox.SelectedItem) = "" Then
				MsgBox(Config.GetValueByName("notselect"), MsgBoxStyle.Exclamation, Config.GetValueByName("notselect_title"))

				Return
			End If
			''''''''''''''''''''''''''''''''''''''''''''''''''''

			metaDataUrl = """" + Config.GetDirectoryByIndex(1) + "application\" + CStr(OldListBox.SelectedItem) + ".xml"""
			rootDirectoryUrl = """" + Config.GetDirectoryByIndex(2) + "old"""
		End If

		''''''''''''''''''''拼接命令行''''''''''''''''''''
		commandLine = batUrl + " " + adlUrl + " " + runTimeUrl + " " + metaDataUrl + " " + rootDirectoryUrl
		''''''''''''''''''''''''''''''''''''''''''''''''''

		''''''''''''''''''''执行命令行''''''''''''''''''''
		Try
			Shell(commandLine, AppWinStyle.Hide)
		Catch ex As Exception
			MsgBox(Config.GetValueByName("execute"), MsgBoxStyle.Critical, Config.GetValueByName("execute_title"))

			Return
		End Try
		''''''''''''''''''''''''''''''''''''''''''''''''''
	End Sub

	''' <summary>
	''' 侦听旧版单项选择按钮
	''' </summary>
	''' <param name="sender">发送器</param>
	''' <param name="e">事件参数</param>
	Private Sub OldRadioButton_CheckedChanged(sender As Object, e As EventArgs) Handles OldRadioButton.CheckedChanged
		OldListBox.Enabled = True
		NewListBox.Enabled = False
		NewListBox.ClearSelected()
	End Sub

	''' <summary>
	''' 侦听新版单项选择按钮
	''' </summary>
	''' <param name="sender">发送器</param>
	''' <param name="e">事件参数</param>
	Private Sub NewRadioButton_CheckedChanged(sender As Object, e As EventArgs) Handles NewRadioButton.CheckedChanged
		OldListBox.Enabled = False
		NewListBox.Enabled = True
		OldListBox.ClearSelected()
	End Sub

End Class
