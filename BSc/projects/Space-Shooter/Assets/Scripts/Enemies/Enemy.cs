using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public int hp;
    public int money;
    public int penalty;
    public float speed;
    public float cooldown;
    public float threshold = -10;
    public float bonusChance = 0.99f;

    public Bullet bullet;
    public Ability ability;
    public Bonus[] bonuses;

    protected Player player;

    protected bool paused = false;

    public void Pause()
    {
        paused = true;
    }

    public void Unpause()
    {
        paused = false;
    }

    private void OnTriggerEnter2D(Collider2D collider)
    {
        if(collider.gameObject.CompareTag("PlayerBullet"))
        {
            DecreaseHp(collider.gameObject.GetComponent<Bullet>().damage);
        }    
    }

    public void DecreaseHp(int damage)
    {
        hp -= damage;

        if (hp <= 0 && player)
        {
            hp = 100; // pt evitarea unui bug cand inamicul 
                      // e lovit fatal de mai multe gloante in acelasi timp

            DropBonus();

            player.IncreaseMoney(money);
            player.DecreaseEnemyCounter();

            Destroy(this.gameObject);
            return;
        }
    }

    private void DropBonus()
    {
        if (bonusChance > Random.Range(0.0f, 1.0f))
        {
            int bonusIndex = Random.Range(0, bonuses.Length);

            Vector3 position = transform.position;
            Quaternion rotation = transform.rotation;

            position.y -= 0.7f;

            Instantiate(bonuses[bonusIndex], position, rotation);
        }
    }
}
