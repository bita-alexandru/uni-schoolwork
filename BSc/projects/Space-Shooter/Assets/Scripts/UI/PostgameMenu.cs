using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class PostgameMenu : MonoBehaviour
{
    public string currentLevel;
    public string nextLevel;

    public GameObject panelFail;
    public Text failRetry;
    public Text failQuit;

    public GameObject panelSuccess;
    public Text successAdvance;
    public Text successRetry;
    public Text successQuit;
    public Text successMoney;

    public Text successHp;
    public Text successAtkSpeed;
    public Text successMovSpeed;

    int state; // 0 = nivel castigat, 1 = nivel pierdut
    int selection = 0;
    int money = 0;

    int currentHp;
    float currentAtkSpeed;
    float currentMovSpeed;

    // Start is called before the first frame update
    void Start()
    {
        ReadDataFile();
        ShowUpgradesInfo();

        failRetry.fontStyle = FontStyle.BoldAndItalic;
        successHp.fontStyle = FontStyle.Bold;
    }

    // Update is called once per frame
    void Update()
    {
        if (state == 0)
        {
            ShowFailMenu();
        }
        else if (state == 1)
        {
            ShowSuccessMenu();
        }
    }

    public void SetState(int state, int money = 0)
    {
        this.state = state;
        this.money = money;

        if (state == 0) // nivel pierdut
        {
            panelFail.SetActive(true);
        }
        else if (state == 1) // nivel castigat
        {
            panelSuccess.SetActive(true);
            successMoney.text = "$" + money.ToString();
        }
    }

    void ShowFailMenu()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            selection = (selection - 1) % 2;
            UpdateFailMenu();
            return;
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            selection = (selection + 1) % 2;
            UpdateFailMenu();
            return;
        }

        if (Input.GetKeyDown(KeyCode.Return))
        {
            MakeFailSelection();
            return;
        }
    }

    void ShowSuccessMenu()
    {
        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            selection = (selection - 1) % 6;
            UpdateSuccessMenu();
            return;
        }

        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            selection = (selection + 1) % 6;
            UpdateSuccessMenu();
            return;
        }

        if (Input.GetKeyDown(KeyCode.Return))
        {
            MakeSuccessSelection();
            return;
        }
    }

    void UpdateFailMenu()
    {
        Text[] options = new Text[] { failRetry, failQuit };

        foreach (Text option in options)
        {
            option.fontStyle = FontStyle.Normal;
        }

        selection = (selection + 2) % 2;

        options[selection].fontStyle = FontStyle.BoldAndItalic;
    }

    void MakeFailSelection()
    {
        switch (selection)
        {
            case 0: // retry
                SceneManager.LoadScene(currentLevel);
                break;
            case 1: // quit to main menu
                SceneManager.LoadScene("StartMenu");
                break;
        }
    }

    void UpdateSuccessMenu()
    {
        Text[] options = new Text[] { 
            successHp, successAtkSpeed, successMovSpeed,
            successAdvance, successRetry, successQuit
        };

        foreach (Text option in options)
        {
            option.fontStyle = FontStyle.Normal;
        }

        selection = (selection + 6) % 6;

        options[selection].fontStyle = FontStyle.Bold;
    }

    void MakeSuccessSelection()
    {
        switch (selection)
        {
            case 0: // hp
                BuyUpgrade("HP");
                break;
            case 1: // atk speed
                BuyUpgrade("ATK SPEED");
                break;
            case 2: // movement speed
                BuyUpgrade("MOV SPEED");
                break;
            case 3: // advance
                SetDataFile();
                SceneManager.LoadScene(nextLevel);
                break;
            case 4: // retry
                SceneManager.LoadScene(currentLevel);
                break;
            case 5: // quit to main menu
                SceneManager.LoadScene("StartMenu");
                break;
        }
    }

    void BuyUpgrade(string upgrade)
    {
        if (money - 1 >= 0)
        {
            money -= 1;
            successMoney.text = "$" + money.ToString();

            switch (upgrade)
            {
                case "HP":
                    currentHp += 1;
                    ShowHpInfo();
                    break;
                case "ATK SPEED":
                    currentAtkSpeed = currentAtkSpeed - currentAtkSpeed * 0.03f;
                    ShowAtkSpeedInfo();
                    break;
                case "MOV SPEED":
                    currentMovSpeed = currentMovSpeed + currentMovSpeed * 0.03f;
                    ShowMovSpeedInfo();
                    break;
            }
        }
    }

    void ReadDataFile()
    {
        string path = "Data/player.txt";
        StreamReader reader = new StreamReader(path);

        while (!reader.EndOfStream)
        {
            string data = reader.ReadLine();
            var field = data.Split(":"[0]);
            var key = field[0];
            var value = field[1];

            switch (key)
            {
                case "maxHp":
                    currentHp = int.Parse(value);
                    break;
                case "maxSpeed":
                    currentMovSpeed = float.Parse(value);
                    break;
                case "maxAtkSpeed":
                    currentAtkSpeed = float.Parse(value);
                    break;
            }
        }

        reader.Close();
    }

    void ShowUpgradesInfo()
    {
        ShowHpInfo();
        ShowAtkSpeedInfo();
        ShowMovSpeedInfo();
    }

    void ShowHpInfo()
    {
        int price = 1;
        string info = currentHp.ToString() + "  -> " + (currentHp + 1).ToString() + " [" + price.ToString() + " ]";

        successHp.text = info;
    }

    void ShowAtkSpeedInfo()
    {
        int price = 1;
        string info = string.Format("{0:#0.00} -> {1:#0.00} [{2}]", currentAtkSpeed, currentAtkSpeed - currentAtkSpeed * 0.03f, price);
        successAtkSpeed.text = info;
    }

    void ShowMovSpeedInfo()
    {
        int price = 1;
        string info = string.Format("{0:#0.00} -> {1:#0.00} [{2}]", currentMovSpeed, currentMovSpeed + currentMovSpeed * 0.03f, price);
        successMovSpeed.text = info;
    }

    void SetDataFile()
    {
        string path = "Data/player.txt";
        Dictionary<string, string> playerData = new Dictionary<string, string>();

        playerData.Add("hp", currentHp.ToString());
        playerData.Add("maxHp", currentHp.ToString());
        playerData.Add("speed", currentMovSpeed.ToString());
        playerData.Add("maxSpeed", currentMovSpeed.ToString());
        playerData.Add("atkSpeed", currentAtkSpeed.ToString());
        playerData.Add("maxAtkSpeed", currentAtkSpeed.ToString());
        playerData.Add("money", money.ToString());

        StreamWriter writer = new StreamWriter(path);

        foreach (var entry in playerData)
            writer.WriteLine("{0}:{1}", entry.Key, entry.Value);
        writer.Close();
    }
}
