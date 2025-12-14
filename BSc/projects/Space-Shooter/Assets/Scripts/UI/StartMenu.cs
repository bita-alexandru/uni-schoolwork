using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class StartMenu : MonoBehaviour
{
    public Text newGame;
    public Text quit;
    
    int selection;

    // Start is called before the first frame update
    void Start()
    {
        SetDataFile();

        newGame.fontStyle = FontStyle.BoldAndItalic;

        selection = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            selection = (selection - 1) % 2;
            UpdateText();
            return;    
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            selection = (selection + 1) % 2;
            UpdateText();
            return;
        }

        if (Input.GetKeyDown(KeyCode.Return))
        {
            MakeSelection();
            return;
        }
    }

    void UpdateText()
    {
        selection = (selection + 2) % 2;

        if (selection == 0)
        {
            newGame.fontStyle = FontStyle.BoldAndItalic;
            quit.fontStyle = FontStyle.Normal;
            return;
        }

        if (selection == 1)
        {
            quit.fontStyle = FontStyle.BoldAndItalic;
            newGame.fontStyle = FontStyle.Normal;
            return;
        }
    }

    void MakeSelection()
    {
        if (selection == 0)
        {
            SceneManager.LoadScene("Level1");
            return;
        }

        if (selection == 1)
        {
            Application.Quit();
        }
    }

    void SetDataFile()
    {
        System.IO.Directory.CreateDirectory("Data");

        string path = "Data/player.txt";
        Dictionary<string, string> playerData = new Dictionary<string, string>();

        playerData.Add("hp", "3");
        playerData.Add("maxHp", "3");
        playerData.Add("speed", "7");
        playerData.Add("maxSpeed", "7");
        playerData.Add("atkSpeed", "0,5");
        playerData.Add("maxAtkSpeed", "0,5");
        playerData.Add("money", "0");

        StreamWriter writer = new StreamWriter(path);

        foreach (var entry in playerData)
            writer.WriteLine("{0}:{1}", entry.Key, entry.Value);
        writer.Close();
    }
}
