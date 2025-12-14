using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbilityEnemyC : Ability
{
    public float speed = 3;
    public int damage = 2;
    private bool abilityMov = true;
    private float timer;
    private float penaltyTime = 3;
    float threshold = -10f;

    // Start is called before the first frame update
    void Start()
    {
        effect = "ROOT";
        duration = 3;

        player = FindObjectOfType<Player>();

        timer = 0;
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

        if (transform.position.y < threshold)
        {
            Destroy(this.gameObject);
            return;
        }

        if (abilityMov == true)
        {
            Vector3 movement = new Vector3(0, speed * Time.deltaTime);
            transform.Translate(movement);
        }

        if (abilityMov == false)
        {
            if (timer >= penaltyTime)
            {
                Destroy(this.gameObject);
                return;
            }
            
            timer = timer + Time.deltaTime;
        }
    }

    private void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.gameObject.CompareTag("PlayerShip"))
        {
            abilityMov = false;
        }
        else if (collider.gameObject.CompareTag("PlayerShield"))
        {
            Destroy(this.gameObject);
        }
    }
}
