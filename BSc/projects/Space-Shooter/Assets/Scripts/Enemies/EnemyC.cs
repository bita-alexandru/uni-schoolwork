using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyC : Enemy
{
    public string direction = "right";

    float timer;
    float abilityTimer;

    // Start is called before the first frame update
    void Start()
    {
        player = FindObjectOfType<Player>();

        string[] directions = { "left", "right" };
        direction = directions[Random.Range(0, 2)];

        timer = 0;
        abilityTimer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (paused) return;
        
        Move();
        Shoot();
    }

    void Move()
    {
        if (!player)
        {
            Destroy(this.gameObject);
            return;
        }

        if (transform.position.y < -6)
        {
            if (player.hp > 0)
            {
                player.DecreaseMoney(penalty);
            }

            Destroy(this.gameObject);
            return;
        }

        if (transform.position.y < 3)
        {

            if (transform.position.x > 8)
            {
                direction = "left";
            }
            if (transform.position.x < -8)
            {
                direction = "right";
            }

            if (string.Equals(direction, "right"))
            {

                transform.Translate(new Vector3(-speed * Time.deltaTime, 0));
            }
            else
            {
                transform.Translate(new Vector3(speed * Time.deltaTime, 0));
            }
        }
        else
        {
            transform.Translate(new Vector3(0, speed * Time.deltaTime));
        }
    }

    void Shoot()
    {
        if (abilityTimer >= 2*cooldown)
        {
            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y -= 0.7f;

            Instantiate(ability, position, rotation);

            abilityTimer = 0;
            timer = 0;
        }
        else if (timer >= cooldown) {
            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y -= 0.7f;

            Instantiate(bullet, position, rotation);
            Instantiate(bullet, position, rotation * Quaternion.Euler(Vector3.forward * 15));
            Instantiate(bullet, position, rotation * Quaternion.Euler(Vector3.back * 15));

            timer = 0;
        }
        else
        {
            timer += Time.deltaTime;
            abilityTimer += Time.deltaTime;
        }
    }
}
