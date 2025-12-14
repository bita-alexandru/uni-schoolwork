using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BonusMovSpeed : Bonus
{
    // Start is called before the first frame update
    void Start()
    {
        type = "MOV SPEED";
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

        transform.Translate(new Vector3(0, speed * Time.deltaTime));
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("PlayerShip"))
        {
            Destroy(this.gameObject);
            return;
        }
    }
}
