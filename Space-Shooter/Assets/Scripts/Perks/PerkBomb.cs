using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PerkBomb : Bullet
{
    public float maxDistance = 5.0f;
    public float explosionTime = 0.5f;
    float increment = 10.5f; 

    float distance = 0;
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

        if (transform.position.y > threshold)
        {
            Destroy(this.gameObject);
            return;
        }

        if (distance >= maxDistance)
        {
            Explode();
            return;
        }

        Vector3 movement = new Vector3(0, speed * Time.deltaTime);

        transform.Translate(movement);
        distance += Mathf.Abs(movement.y);
    }

    private void OnTriggerEnter2D(Collider2D collider)
    {
        if (collider.gameObject.CompareTag("EnemyShip"))
        {
            Explode();
        }
    }

    private void Explode()
    {
        if (explosionTime < 0.0f)
        {
            Destroy(this.gameObject);
            return;
        }
        
        // e destul sa scalam obiectul in sine deoarece in felul asta
        // se scaleaza si raza collider-ului
        GetComponentInParent<Transform>().localScale += new Vector3(increment*Time.deltaTime,increment*Time.deltaTime,0);
        // GetComponentInParent<CircleCollider2D>().radius += (increment * Time.deltaTime);

        explosionTime -= Time.deltaTime;
    }
}
