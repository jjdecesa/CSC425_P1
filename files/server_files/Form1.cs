using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Lottery_Numbers
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void generateButton_Click(object sender, EventArgs e)
        {           

            // Array to hold numbers
            const int SIZE = 5;
            // int[] lotteryNumbers = new int[SIZE];
            
            System.Windows.Forms.Label[] labelList = new System.Windows.Forms.Label[SIZE];

            labelList[0] = firstLabel;
            labelList[1] = secondLabel;
            labelList[2] = thirdLabel;
            labelList[3] = fourthLabel;
            labelList[4] = fifthLabel;

            // Create a random object
            Random rand = new Random();

            // Fill array with random numbers in the range of 0 to 99
            for (int index = 0; index < SIZE; index++)
            {
                // lotteryNumbers[index] = rand.Next(100);

                labelList[index].Text = rand.Next(100).ToString();

            }

            // Display the array elements in the Label controls.
            //firstLabel.Text = lotteryNumbers[0].ToString();
            //secondLabel.Text = lotteryNumbers[1].ToString();
            //thirdLabel.Text = lotteryNumbers[2].ToString();
            //fourthLabel.Text = lotteryNumbers[3].ToString();
            //fifthLabel.Text = lotteryNumbers[4].ToString();

        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}


/*
  System.Windows.Forms.Label[] labelList = new System.Windows.Forms.Label[SIZE];

            labelList[0] = firstLabel;
            labelList[1] = secondLabel;
            labelList[2] = thirdLabel;
            labelList[3] = fourthLabel;
            labelList[4] = fifthLabel;

   labelList[index].Text = lotteryNumbers[index].ToString();
*/