using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public int hp = 5;
    public int maxHp = 5;
    public int money = 0;

    public float atkSpeed = 0.5f;
    public float maxAtkSpeed = 0.5f;
    float cooldownAtk = -1;
    float bonusTimeAtkSpeed = -1;

    public float speed = 7;
    public float maxSpeed = 7;
    float bonusTimeSpeed = -1;

    float maxBonusTime = 10;
    public Bullet bullet;
    Canvas canvas;
    IngameMenu ingameMenu;

    int enemyCounter;
    const float x_min = -11;
    const float x_max = 11;
    const float y_min = -4.5f;
    const float y_max = 4.5f;

    string effectCurrent = "NONE";
    float effectDuration = 0;

    int countBullets = 1;
    int maxBullets = 4;

    float cooldownBomb = -1;
    float cooldownShield = -1;
    public float downtimeBomb = 10;
    public float downtimeShield = 10;
    public string specialAbility = "None";

    public PerkBomb perkBomb;
    public PerkShield perkShield;
    public Bonus perkSpecial;

    public PopupText popupText;

    bool paused = false;

    // Start is called before the first frame update
    void Start()
    {
        ReadDataFile();

        canvas = FindObjectOfType<Canvas>();
        ingameMenu = canvas.GetComponent<IngameMenu>();
        
        ingameMenu.UpdateHp(hp);
        ingameMenu.UpdateMoney(money);

        ingameMenu.UpdateBomb(-1);
        ingameMenu.UpdateShield(-1);
        ingameMenu.UpdateSpecial(specialAbility);
    }

    // Update is called once per frame
    void Update()
    {
        if (paused) return;
        
        UpdateCooldowns();

        Move();
        Shoot();
        UseAbilities();
        
        UpdateEffect();
        UpdateBonuses();
    }

    void Move()
    {
        if (effectCurrent == "ROOT")
        {
            return;
        }
        
        Vector3 movement = new Vector3(0, 0);

        /* Miscarea orizontala */
        if(Input.GetKey(KeyCode.LeftArrow))
        {
            movement += new Vector3(-speed * Time.deltaTime, 0);
        }

        if (Input.GetKey(KeyCode.RightArrow))
        {
            movement += new Vector3(speed * Time.deltaTime, 0);
        }


        /* Miscarea verticala */
        if (Input.GetKey(KeyCode.UpArrow))
        {
            movement += new Vector3(0, speed * Time.deltaTime);
        }

        if (Input.GetKey(KeyCode.DownArrow))
        {
            movement += new Vector3(0, -speed * Time.deltaTime);
        }

        if (movement != new Vector3(0, 0))
        {
            movement = movement.normalized * speed * Time.deltaTime;

            transform.Translate(movement);

            Vector3 position = transform.position;
            position.x = Mathf.Clamp(position.x, x_min, x_max);
            position.y = Mathf.Clamp(position.y, y_min, y_max);

            transform.position = position;
        }
    }

    void Shoot()
    {
        if (Input.GetKey(KeyCode.Space) && cooldownAtk == -1)
        {
            cooldownAtk = 0;

            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y += 0.7f;

            switch (countBullets)
            {
                case 1:
                    Instantiate(bullet, position, rotation);
                    break;
                case 2:
                    Instantiate(bullet, position + Vector3.left * 0.2f, rotation);
                    Instantiate(bullet, position + Vector3.right * 0.2f, rotation);
                    break;
                case 3:
                    Instantiate(bullet, position, rotation);
                    Instantiate(
                        bullet,
                        position + Vector3.left * 0.55f + Vector3.down * 0.4f,
                        rotation
                        );
                    Instantiate(
                        bullet,
                        position + Vector3.right * 0.55f + Vector3.down * 0.4f,
                        rotation
                        );
                    break;
                case 4:
                    Instantiate(bullet, position + Vector3.left * 0.2f, rotation);
                    Instantiate(bullet, position + Vector3.right * 0.2f, rotation);
                    Instantiate(
                        bullet,
                        position + Vector3.left * 0.55f + Vector3.down * 0.4f,
                        rotation
                        );
                    Instantiate(
                        bullet,
                        position + Vector3.right * 0.55f + Vector3.down * 0.4f,
                        rotation
                        );
                    break;
            }
        }
    }

    void UseAbilities()
    {
        if (Input.GetKey(KeyCode.Z) && cooldownBomb == -1)
        {
            cooldownBomb = 0;

            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y += 0.7f;
            
            Instantiate(perkBomb, position, rotation); 
        }

        if (Input.GetKey(KeyCode.X) && cooldownShield == -1)
        {
            cooldownShield = 0;

            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            Instantiate(perkShield, position, rotation);

            effectCurrent = "NONE";
            effectDuration = 0f;
        }

        if (Input.GetKey(KeyCode.Y) && specialAbility != "None")
        {
            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y += 0.7f;
            
            Instantiate(bullet, position, rotation); 
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("EnemyBullet"))
        {
            DecreaseHp(collision.gameObject.GetComponent<Bullet>().damage);

            return;
        }
        
        if(collision.gameObject.CompareTag("EnemyAbility"))
        {
            Ability ability = collision.gameObject.GetComponent<Ability>();

            SetEffect(ability.effect, ability.duration);

            return;
        }

        if (collision.gameObject.CompareTag("Bonus"))
        {
            Bonus bonus = collision.gameObject.GetComponent<Bonus>();

            SetBonus(bonus.type);

            return;
        }
    }

    public void IncreaseMoney(int ammount)
    {
        money += ammount;
        ingameMenu.UpdateMoney(money);
    }

    public void DecreaseHp(int damage)
    {
        hp -= damage;
        ingameMenu.UpdateHp(hp);

        if (hp <= 0)
        {
            ingameMenu.UpdateState(0); // 0 = nivel pierdut
            Destroy(this.gameObject);
        }
    }

    public void DecreaseMoney(int penalty)
    {
        money = Mathf.Max(0, money - penalty);
        ingameMenu.UpdateMoney(money);
    }

    public void SetEnemyCounter(int counter)
    {
        enemyCounter = counter;
    }

    public void DecreaseEnemyCounter()
    {
        enemyCounter--;
        if (enemyCounter == 0)
        {
            ingameMenu.UpdateState(1, money); // 1 = nivel castigat
            Destroy(this.gameObject);
        }
    }

    void SetEffect(string effect, float duration)
    {
        effectCurrent = effect;
        effectDuration = duration;

        string message;

        switch(effect)
        {
            case "ROOT":
            {
                message = "rooted in place";
                break;
            }
            default:
            {
                message = "awkward...";
                break;
            }
        }

        MakePopup(message, "DEBUFF");
    }

    void UpdateEffect()
    {
        if (effectDuration <= 0f)
        {
            effectCurrent = "NONE";
        }

        effectDuration -= Time.deltaTime;
    }

    void SetBonus(string type)
    {
        string message;

        switch (type)
        {
            case "HP":
            {
                hp = Mathf.Min(maxHp, hp + 1);
                ingameMenu.UpdateHp(hp);
                message = "heal 1 hp";
                break;
            }
            case "ATK SPEED":
            {
                bonusTimeAtkSpeed = 0;
                atkSpeed *= 0.9f; // 10% bonus
                message = "+10% attack speed";
                break;
            }
            case "MOV SPEED":
            {
                bonusTimeSpeed = 0;
                speed *= 1.1f; // 10% bonus
                message = "+10% speed";
                break;
            }
            case "BULLETS":
            {
                countBullets = Mathf.Min(maxBullets, countBullets + 1);
                message = "+1 bullet";
                break;
            }
            default:
            {
                message = "this is awkward";
                break;
            }
        }

        MakePopup(message, "BUFF");
    }

    void UpdateCooldowns()
    {
        if (cooldownAtk != -1)
        {
            cooldownAtk += Time.deltaTime;

            if (cooldownAtk >= atkSpeed)
            {
                cooldownAtk = -1;
            }
        }

        if (cooldownBomb != -1)
        {
            cooldownBomb += Time.deltaTime;

            if (cooldownBomb >= downtimeBomb)
            {
                cooldownBomb = -1;

                ingameMenu.UpdateBomb(-1);
                return;
            }

            int s = Mathf.CeilToInt(downtimeBomb - cooldownBomb);
            ingameMenu.UpdateBomb(s);
        }

        if (cooldownShield != -1)
        {
            cooldownShield += Time.deltaTime;

            if (cooldownShield >= downtimeShield)
            {
                cooldownShield = -1;
                ingameMenu.UpdateShield(-1);
                return;
            }

            int s = Mathf.CeilToInt(downtimeShield - cooldownShield);
            ingameMenu.UpdateShield(s);
        }
    }

    void UpdateBonuses()
    {
        if (bonusTimeAtkSpeed != -1)
        {
            bonusTimeAtkSpeed += Time.deltaTime;

            if (bonusTimeAtkSpeed >= maxBonusTime)
            {
                bonusTimeAtkSpeed = -1;
                atkSpeed = maxAtkSpeed;
            }
        }

        if (bonusTimeSpeed != -1)
        {
            bonusTimeSpeed += Time.deltaTime;

            if (bonusTimeSpeed >= maxBonusTime)
            {
                bonusTimeSpeed = -1;
                speed = maxSpeed;
            }
        }
    }

    void MakePopup(string message, string type)
    {
        // efecte: FADE OUT, FADE IN, FADE IN OUT, TYPEWRITER
        Vector3 position = transform.position + Vector3.up*0.8f;
        string effect = "FADE OUT";
        float displayTime = 0.5f;

        PopupText popup = Instantiate(popupText, position, Quaternion.identity);
        popup.Setup(message, effect, displayTime);

        Color color;
        if (type == "BUFF")
        {
            color = Color.green;
        }
        else
        {
            color = Color.magenta;
        }

        popup.SetColor(color);
    }

    public void Pause()
    {
        paused = true;
    }

    public void Unpause()
    {
        paused = false;
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
                case "hp":
                    hp = int.Parse(value);
                    break;
                case "maxHp":
                    maxHp = int.Parse(value);
                    break;
                case "speed":
                    speed = float.Parse(value);
                    break;
                case "maxSpeed":
                    maxSpeed = float.Parse(value);
                    break;
                case "atkSpeed":
                    atkSpeed = float.Parse(value);
                    break;
                case "maxAtkSpeed":
                    maxAtkSpeed = float.Parse(value);
                    break;
                case "money":
                    money = int.Parse(value);
                    break;
            }
        }

        reader.Close();
    }
}
