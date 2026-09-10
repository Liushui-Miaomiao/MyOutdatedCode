<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.NewListBox = New System.Windows.Forms.ListBox()
        Me.OldListBox = New System.Windows.Forms.ListBox()
        Me.NewRadioButton = New System.Windows.Forms.RadioButton()
        Me.OldRadioButton = New System.Windows.Forms.RadioButton()
        Me.LaunchButton = New System.Windows.Forms.Button()
        Me.SelectLable = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'NewListBox
        '
        Me.NewListBox.FormattingEnabled = True
        Me.NewListBox.ItemHeight = 12
        Me.NewListBox.Location = New System.Drawing.Point(21, 170)
        Me.NewListBox.Name = "NewListBox"
        Me.NewListBox.Size = New System.Drawing.Size(250, 52)
        Me.NewListBox.TabIndex = 11
        '
        'OldListBox
        '
        Me.OldListBox.Enabled = False
        Me.OldListBox.FormattingEnabled = True
        Me.OldListBox.ItemHeight = 12
        Me.OldListBox.Location = New System.Drawing.Point(21, 80)
        Me.OldListBox.Name = "OldListBox"
        Me.OldListBox.Size = New System.Drawing.Size(250, 52)
        Me.OldListBox.TabIndex = 10
        '
        'NewRadioButton
        '
        Me.NewRadioButton.AutoSize = True
        Me.NewRadioButton.Checked = True
        Me.NewRadioButton.Location = New System.Drawing.Point(21, 145)
        Me.NewRadioButton.Name = "NewRadioButton"
        Me.NewRadioButton.Size = New System.Drawing.Size(107, 16)
        Me.NewRadioButton.TabIndex = 9
        Me.NewRadioButton.TabStop = True
        Me.NewRadioButton.Text = "NewRadioButton"
        Me.NewRadioButton.UseVisualStyleBackColor = True
        '
        'OldRadioButton
        '
        Me.OldRadioButton.AutoSize = True
        Me.OldRadioButton.Location = New System.Drawing.Point(21, 55)
        Me.OldRadioButton.Name = "OldRadioButton"
        Me.OldRadioButton.Size = New System.Drawing.Size(107, 16)
        Me.OldRadioButton.TabIndex = 8
        Me.OldRadioButton.Text = "OldRadioButton"
        Me.OldRadioButton.UseVisualStyleBackColor = True
        '
        'LaunchButton
        '
        Me.LaunchButton.Location = New System.Drawing.Point(81, 249)
        Me.LaunchButton.Name = "LaunchButton"
        Me.LaunchButton.Size = New System.Drawing.Size(120, 40)
        Me.LaunchButton.TabIndex = 7
        Me.LaunchButton.Text = "LaunchButton"
        Me.LaunchButton.UseVisualStyleBackColor = True
        '
        'SelectLable
        '
        Me.SelectLable.Location = New System.Drawing.Point(1, 21)
        Me.SelectLable.Name = "SelectLable"
        Me.SelectLable.Size = New System.Drawing.Size(280, 12)
        Me.SelectLable.TabIndex = 6
        Me.SelectLable.Text = "SelectLable"
        Me.SelectLable.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(282, 310)
        Me.Controls.Add(Me.NewListBox)
        Me.Controls.Add(Me.OldListBox)
        Me.Controls.Add(Me.NewRadioButton)
        Me.Controls.Add(Me.OldRadioButton)
        Me.Controls.Add(Me.LaunchButton)
        Me.Controls.Add(Me.SelectLable)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents NewListBox As ListBox
    Friend WithEvents OldListBox As ListBox
    Friend WithEvents NewRadioButton As RadioButton
    Friend WithEvents OldRadioButton As RadioButton
    Friend WithEvents LaunchButton As Button
    Friend WithEvents SelectLable As Label
End Class
