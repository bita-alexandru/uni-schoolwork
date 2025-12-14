using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyB : Enemy
{
    float timer;

    // Start is called before the first frame update
    void Start()
    {
        player = FindObjectOfType<Player>();

        timer = 0;
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

        if (transform.position.y < threshold)
        {
            if (player)
            {
                player.DecreaseMoney(penalty);
                player.DecreaseEnemyCounter();
            }

            Destroy(this.gameObject);
            return;
        }

        transform.Translate(new Vector3(0, speed * Time.deltaTime));
    }

    void Shoot()
    {
        if (timer >= cooldown)
        {
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
        }
    }
}
