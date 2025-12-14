using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletEnemyB : Bullet
{
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
        
        if (transform.position.y < threshold)
        {
            Destroy(this.gameObject);
            return;
        }

        Vector3 movement = new Vector3(0, speed * Time.deltaTime);

        transform.Translate(movement);
    }

    private void OnTriggerEnter2D(Collider2D collider)
    {
        if (
            collider.gameObject.CompareTag("PlayerShip")
            || collider.gameObject.CompareTag("PlayerShield")
            )
        {
            Destroy(this.gameObject);
            return;
        }
    }
}
