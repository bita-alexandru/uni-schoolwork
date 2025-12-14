using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class IngameMenu : MonoBehaviour
{
    public GameObject abilitiesMenu;
    public GameObject statsMenu;
    public Text hp;
    public Text money;
    public Text bomb;
    public Text shield;
    public Text special;

    PostgameMenu postgameMenu;

    bool paused = false;

    // Start is called before the first frame update
    void Start()
    {
        postgameMenu = GetComponentInParent<PostgameMenu>();
    }
    
    void Update()
    {
        if (Input.GetKey(KeyCode.R))
        {
            SceneManager.LoadScene(postgameMenu.currentLevel);
        }

        if (Input.GetKey(KeyCode.Escape))
        {
            SceneManager.LoadScene("StartMenu");
        }

        if (!paused && Input.GetKey(KeyCode.S))
        {
            Enemy[] enemies = FindObjectsOfType<Enemy>();
            Ability[] abilities = FindObjectsOfType<Ability>();
            Bullet[] bullets = FindObjectsOfType<Bullet>();
            Bonus[] bonuses = FindObjectsOfType<Bonus>();
            Pausable[] pausables = FindObjectsOfType<Pausable>();
            Level level = FindObjectOfType<Level>();
            Spawner spawner = FindObjectOfType<Spawner>();
            Player player = FindObjectOfType<Player>();

            foreach (Enemy enemy in enemies) enemy.Pause();
            foreach (Ability ability in abilities) ability.Pause();
            foreach (Bullet bullet in bullets) bullet.Pause();
            foreach (Bonus bonus in bonuses) bonus.Pause();
            foreach (Pausable pausable in pausables) pausable.Pause();
            
            if (level) level.Pause();
            if (spawner) spawner.Pause();
            player.Pause();

            paused = true;

            return;
        }

        if (paused && Input.GetKey(KeyCode.D))
        {
            Enemy[] enemies = FindObjectsOfType<Enemy>();
            Ability[] abilities = FindObjectsOfType<Ability>();
            Bullet[] bullets = FindObjectsOfType<Bullet>();
            Bonus[] bonuses = FindObjectsOfType<Bonus>();
            Pausable[] pausables = FindObjectsOfType<Pausable>();
            Level level = FindObjectOfType<Level>();
            Spawner spawner = FindObjectOfType<Spawner>();
            Player player = FindObjectOfType<Player>();

            foreach (Enemy enemy in enemies) enemy.Unpause();
            foreach (Ability ability in abilities) ability.Unpause();
            foreach (Bullet bullet in bullets) bullet.Unpause();
            foreach (Bonus bonus in bonuses) bonus.Unpause();
            foreach (Pausable pausable in pausables) pausable.Unpause();
            
            if (level) level.Unpause();
            if (spawner) spawner.Unpause();
            player.Unpause();

            paused = false;

            return;
        }
    }

    public void UpdateHp(int hp)
    {
        this.hp.text = hp.ToString();
    }

    public void UpdateMoney(int money)
    {
        this.money.text = "$" + money.ToString();
    }

    public void UpdateState(int state, int money = 0)
    {
        abilitiesMenu.SetActive(false);
        statsMenu.SetActive(false);

        postgameMenu.enabled = true;
        postgameMenu.SetState(state, money); // 0 = nivel pierdut, 1 = nivel castigat

        Destroy(this);
    }

    public void UpdateBomb(int cooldown)
    {
        if (cooldown == -1)
        {
            this.bomb.text = "Available";
        }
        else
        {
            this.bomb.text = cooldown.ToString() + "s";
        }
    }

    public void UpdateShield(int cooldown)
    {
        if (cooldown == -1)
        {
            this.shield.text = "Available";
        }
        else
        {
            this.shield.text = cooldown.ToString() + "s";
        }
    }

    public void UpdateSpecial(string name)
    {
        this.special.text = name;
    }
}
