/*
 * Created by SharpDevelop.
 * User: m_pek
 * Date: 12/18/2024
 * Time: 1:16 AM
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace LCDSeriPortson
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class MainForm : Form
	{
		string gelenveri = string.Empty;
		public MainForm()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		void BaslangicDegerGonderClick(object sender, EventArgs e)
		{
	        // Tek bir TextBox'tan saati al: "HH:MM:SS" formatında
            string zaman = zamanTextBox.Text; // "HH:MM:SS"

            if (zaman.Length != 8 || zaman[2] != ':' || zaman[5] != ':')
            {
                MessageBox.Show("Lütfen saati 'HH:MM:SS' formatında giriniz!", "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // UART ile zaman stringini gönder
            VeriGonder(zaman);
		}
		private void VeriGonder(string zaman)
        {
            // Stringi gönder (tek seferde 8 karakter "HH:MM:SS")
            serialPort1.Write(zaman);
            System.Threading.Thread.Sleep(1000); // 100 ms bekleme
            
        }
		void SaatAlClick(object sender, EventArgs e)
		{
	        // 8 karakterlik bir tampon oluştur
        char[] buffer2 = new char[8]; // "HH:MM:SS" formatı için

        // 8 karakteri bir seferde oku
        for (int i = 0; i < 8; i++)
        {
            buffer2[i] = (char)serialPort1.ReadChar(); // Seri port üzerinden karakter oku
        }

        // Okunan 8 karakteri birleştir
        string gelenZaman = new string(buffer2);

        // Zaman bilgisini ekrana yazdır
        zamanTextBox2.Text = gelenZaman;
		}
		void BtnacClick(object sender, EventArgs e)
		{
			if(!serialPort1.IsOpen){
			serialPort1.PortName = textcom.Text;
			serialPort1.BaudRate = Convert.ToInt32(textBoudrate.Text);
			serialPort1.DataBits = Convert.ToInt32(textdatabits.Text);
			serialPort1.Open();
			//serialPort1.DiscardInBuffer();
			//serialPort1.DiscardOutBuffer();
			//serialPort1.DtrEnable=true;
		}
	}
		void BtnkptClick(object sender, EventArgs e)
		{
			if(serialPort1.IsOpen){
			serialPort1.Close();
		}
	}
		void BtngonderClick(object sender, EventArgs e)
		{
		serialPort1.Write(textgonderilecekveriler.Text);
		}
		void SerialPort1DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
		{
            // Mikrodenetleyiciden gelen satırı oku
            gelenveri = serialPort1.ReadLine().Trim();
            this.Invoke(new EventHandler(DisplayText)); // Gelen veriyi UI'ya gönder
		}
 private void DisplayText(object sender, EventArgs e)
        {            // Gelen veriyi analiz et
            if (gelenveri.StartsWith("ADC:"))
            {
                // ADC değeri kısmını ayıkla
                string adcValue = gelenveri.Substring(4).Trim();
                textBoxADC.Text = adcValue; // ADC verisini ilgili textBox'a yaz
            }


}


	}}
