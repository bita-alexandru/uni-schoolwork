using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerkShield : Pausable
{
    public float maxTime = 5;
    Player player;
    // Start is called before the first frame update
    void Start()
    {
        player = FindObjectOfType<Player>();
    }

    // Update is called once per frame
    void Update()
    {
        if (paused) return;
        
        if (!player)
        {
            Destroy(this.gameObject);
            return;
        }

        if (maxTime <= 0.0f)
        {
            Destroy(this.gameObject);
            return;
        }

        transform.position = player.transform.position;

        maxTime -= Time.deltaTime;
    }

    private void OnTriggerEnter2D(Collider2D collider) 
    {
        if (collider.gameObject.CompareTag("EnemyBullet"))
        {
            maxTime -= 0.5f;
        }
        else if (collider.gameObject.CompareTag("EnemyAbility"))
        {
            maxTime -= 1.0f;
        }
    }
}
