	/*
	 * Created by SharpDevelop.
	 * User: m_pek
	 * Date: 12/18/2024
	 * Time: 1:16 AM
	 * 
	 * To change this template use Tools | Options | Coding | Edit Standard Headers.
	 */
	namespace LCDSeriPortson
	{
		partial class MainForm
		{
			/// <summary>
			/// Designer variable used to keep track of non-visual components.
			/// </summary>
			private System.ComponentModel.IContainer components = null;
			private System.Windows.Forms.Label label1;
			private System.Windows.Forms.Button baslangicDegerGonder;
			private System.Windows.Forms.TextBox zamanTextBox2;
			private System.Windows.Forms.Label label2;
			private System.Windows.Forms.Button SaatAl;
			private System.Windows.Forms.TextBox zamanTextBox;
			private System.IO.Ports.SerialPort serialPort1;
			private System.Windows.Forms.TextBox textBoudrate;
			private System.Windows.Forms.Label label3;
			private System.Windows.Forms.TextBox textcom;
			private System.Windows.Forms.Label label4;
			private System.Windows.Forms.TextBox textdatabits;
			private System.Windows.Forms.Label label5;
			private System.Windows.Forms.Button btnac;
			private System.Windows.Forms.Button btnkpt;
			private System.Windows.Forms.TextBox textBoxADC;
			private System.Windows.Forms.Label label6;
			private System.Windows.Forms.TextBox textBox1;
			private System.Windows.Forms.Label textgelenveriler;
			private System.Windows.Forms.Button btngonder;
			private System.Windows.Forms.TextBox textgonderilecekveriler;
			private System.Windows.Forms.Label label7;
			
			/// <summary>
			/// Disposes resources used by the form.
			/// </summary>
			/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
			protected override void Dispose(bool disposing)
			{
				if (disposing) {
					if (components != null) {
						components.Dispose();
					}
				}
				base.Dispose(disposing);
			}
			
			/// <summary>
			/// This method is required for Windows Forms designer support.
			/// Do not change the method contents inside the source code editor. The Forms designer might
			/// not be able to load this method if it was changed manually.
			/// </summary>
			private void InitializeComponent()
			{
				this.components = new System.ComponentModel.Container();
				this.label1 = new System.Windows.Forms.Label();
				this.zamanTextBox = new System.Windows.Forms.TextBox();
				this.baslangicDegerGonder = new System.Windows.Forms.Button();
				this.zamanTextBox2 = new System.Windows.Forms.TextBox();
				this.label2 = new System.Windows.Forms.Label();
				this.SaatAl = new System.Windows.Forms.Button();
				this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
				this.textBoudrate = new System.Windows.Forms.TextBox();
				this.label3 = new System.Windows.Forms.Label();
				this.textcom = new System.Windows.Forms.TextBox();
				this.label4 = new System.Windows.Forms.Label();
				this.textdatabits = new System.Windows.Forms.TextBox();
				this.label5 = new System.Windows.Forms.Label();
				this.btnac = new System.Windows.Forms.Button();
				this.btnkpt = new System.Windows.Forms.Button();
				this.textBoxADC = new System.Windows.Forms.TextBox();
				this.label6 = new System.Windows.Forms.Label();
				this.textBox1 = new System.Windows.Forms.TextBox();
				this.textgelenveriler = new System.Windows.Forms.Label();
				this.btngonder = new System.Windows.Forms.Button();
				this.textgonderilecekveriler = new System.Windows.Forms.TextBox();
				this.label7 = new System.Windows.Forms.Label();
				this.SuspendLayout();
				// 
				// label1
				// 
				this.label1.Location = new System.Drawing.Point(49, 430);
				this.label1.Name = "label1";
				this.label1.Size = new System.Drawing.Size(108, 17);
				this.label1.TabIndex = 0;
				this.label1.Text = "Gönderilecek Saat";
				// 
				// zamanTextBox
				// 
				this.zamanTextBox.Location = new System.Drawing.Point(176, 430);
				this.zamanTextBox.Name = "zamanTextBox";
				this.zamanTextBox.Size = new System.Drawing.Size(199, 20);
				this.zamanTextBox.TabIndex = 1;
				// 
				// baslangicDegerGonder
				// 
				this.baslangicDegerGonder.Location = new System.Drawing.Point(408, 424);
				this.baslangicDegerGonder.Name = "baslangicDegerGonder";
				this.baslangicDegerGonder.Size = new System.Drawing.Size(88, 30);
				this.baslangicDegerGonder.TabIndex = 2;
				this.baslangicDegerGonder.Text = "Saat Gönder";
				this.baslangicDegerGonder.UseVisualStyleBackColor = true;
				this.baslangicDegerGonder.Click += new System.EventHandler(this.BaslangicDegerGonderClick);
				// 
				// zamanTextBox2
				// 
				this.zamanTextBox2.Location = new System.Drawing.Point(176, 483);
				this.zamanTextBox2.Name = "zamanTextBox2";
				this.zamanTextBox2.Size = new System.Drawing.Size(199, 20);
				this.zamanTextBox2.TabIndex = 4;
				// 
				// label2
				// 
				this.label2.Location = new System.Drawing.Point(49, 483);
				this.label2.Name = "label2";
				this.label2.Size = new System.Drawing.Size(108, 17);
				this.label2.TabIndex = 3;
				this.label2.Text = "Gelen Saat";
				// 
				// SaatAl
				// 
				this.SaatAl.Location = new System.Drawing.Point(408, 477);
				this.SaatAl.Name = "SaatAl";
				this.SaatAl.Size = new System.Drawing.Size(88, 30);
				this.SaatAl.TabIndex = 5;
				this.SaatAl.Text = "Saat Al";
				this.SaatAl.UseVisualStyleBackColor = true;
				this.SaatAl.Click += new System.EventHandler(this.SaatAlClick);
				// 
				// serialPort1
				// 
				this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort1DataReceived);
				// 
				// textBoudrate
				// 
				this.textBoudrate.Location = new System.Drawing.Point(176, 93);
				this.textBoudrate.Name = "textBoudrate";
				this.textBoudrate.Size = new System.Drawing.Size(199, 20);
				this.textBoudrate.TabIndex = 9;
				this.textBoudrate.Text = "9600";
				// 
				// label3
				// 
				this.label3.Location = new System.Drawing.Point(49, 93);
				this.label3.Name = "label3";
				this.label3.Size = new System.Drawing.Size(108, 17);
				this.label3.TabIndex = 8;
				this.label3.Text = "BoudRate";
				// 
				// textcom
				// 
				this.textcom.Location = new System.Drawing.Point(176, 40);
				this.textcom.Name = "textcom";
				this.textcom.Size = new System.Drawing.Size(199, 20);
				this.textcom.TabIndex = 7;
				this.textcom.Text = "COM3";
				// 
				// label4
				// 
				this.label4.Location = new System.Drawing.Point(49, 40);
				this.label4.Name = "label4";
				this.label4.Size = new System.Drawing.Size(108, 17);
				this.label4.TabIndex = 6;
				this.label4.Text = "Com NO";
				// 
				// textdatabits
				// 
				this.textdatabits.Location = new System.Drawing.Point(176, 146);
				this.textdatabits.Name = "textdatabits";
				this.textdatabits.Size = new System.Drawing.Size(199, 20);
				this.textdatabits.TabIndex = 11;
				this.textdatabits.Text = "8";
				// 
				// label5
				// 
				this.label5.Location = new System.Drawing.Point(49, 146);
				this.label5.Name = "label5";
				this.label5.Size = new System.Drawing.Size(108, 17);
				this.label5.TabIndex = 10;
				this.label5.Text = "DataBits";
				// 
				// btnac
				// 
				this.btnac.Location = new System.Drawing.Point(408, 40);
				this.btnac.Name = "btnac";
				this.btnac.Size = new System.Drawing.Size(88, 30);
				this.btnac.TabIndex = 12;
				this.btnac.Text = "Port Aç";
				this.btnac.UseVisualStyleBackColor = true;
				this.btnac.Click += new System.EventHandler(this.BtnacClick);
				// 
				// btnkpt
				// 
				this.btnkpt.Location = new System.Drawing.Point(408, 93);
				this.btnkpt.Name = "btnkpt";
				this.btnkpt.Size = new System.Drawing.Size(88, 30);
				this.btnkpt.TabIndex = 13;
				this.btnkpt.Text = "Port Kapat";
				this.btnkpt.UseVisualStyleBackColor = true;
				this.btnkpt.Click += new System.EventHandler(this.BtnkptClick);
				// 
				// textBoxADC
				// 
				this.textBoxADC.Location = new System.Drawing.Point(176, 335);
				this.textBoxADC.Multiline = true;
				this.textBoxADC.Name = "textBoxADC";
				this.textBoxADC.Size = new System.Drawing.Size(170, 27);
				this.textBoxADC.TabIndex = 21;
				// 
				// label6
				// 
				this.label6.Location = new System.Drawing.Point(49, 344);
				this.label6.Name = "label6";
				this.label6.Size = new System.Drawing.Size(149, 18);
				this.label6.TabIndex = 20;
				this.label6.Text = "ADC veri";
				// 
				// textBox1
				// 
				this.textBox1.BackColor = System.Drawing.SystemColors.Window;
				this.textBox1.ForeColor = System.Drawing.SystemColors.WindowText;
				this.textBox1.Location = new System.Drawing.Point(176, 262);
				this.textBox1.Multiline = true;
				this.textBox1.Name = "textBox1";
				this.textBox1.Size = new System.Drawing.Size(264, 57);
				this.textBox1.TabIndex = 19;
				// 
				// textgelenveriler
				// 
				this.textgelenveriler.Location = new System.Drawing.Point(49, 284);
				this.textgelenveriler.Name = "textgelenveriler";
				this.textgelenveriler.Size = new System.Drawing.Size(122, 21);
				this.textgelenveriler.TabIndex = 18;
				this.textgelenveriler.Text = "Gelen Veri";
				// 
				// btngonder
				// 
				this.btngonder.Location = new System.Drawing.Point(352, 190);
				this.btngonder.Name = "btngonder";
				this.btngonder.Size = new System.Drawing.Size(88, 38);
				this.btngonder.TabIndex = 17;
				this.btngonder.Text = "Gönder";
				this.btngonder.UseVisualStyleBackColor = true;
				this.btngonder.Click += new System.EventHandler(this.BtngonderClick);
				// 
				// textgonderilecekveriler
				// 
				this.textgonderilecekveriler.Location = new System.Drawing.Point(176, 190);
				this.textgonderilecekveriler.Multiline = true;
				this.textgonderilecekveriler.Name = "textgonderilecekveriler";
				this.textgonderilecekveriler.Size = new System.Drawing.Size(143, 38);
				this.textgonderilecekveriler.TabIndex = 16;
				// 
				// label7
				// 
				this.label7.Location = new System.Drawing.Point(49, 207);
				this.label7.Name = "label7";
				this.label7.Size = new System.Drawing.Size(122, 21);
				this.label7.TabIndex = 15;
				this.label7.Text = "Gönderilecek veri";
				// 
				// MainForm
				// 
				this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
				this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
				this.ClientSize = new System.Drawing.Size(532, 529);
				this.Controls.Add(this.textBoxADC);
				this.Controls.Add(this.label6);
				this.Controls.Add(this.textBox1);
				this.Controls.Add(this.textgelenveriler);
				this.Controls.Add(this.btngonder);
				this.Controls.Add(this.textgonderilecekveriler);
				this.Controls.Add(this.label7);
				this.Controls.Add(this.btnkpt);
				this.Controls.Add(this.btnac);
				this.Controls.Add(this.textdatabits);
				this.Controls.Add(this.label5);
				this.Controls.Add(this.textBoudrate);
				this.Controls.Add(this.label3);
				this.Controls.Add(this.textcom);
				this.Controls.Add(this.label4);
				this.Controls.Add(this.SaatAl);
				this.Controls.Add(this.zamanTextBox2);
				this.Controls.Add(this.label2);
				this.Controls.Add(this.baslangicDegerGonder);
				this.Controls.Add(this.zamanTextBox);
				this.Controls.Add(this.label1);
				this.Name = "MainForm";
				this.Text = "LCDSeriPortson";
				this.ResumeLayout(false);
				this.PerformLayout();

			}
		}
	}
